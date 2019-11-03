#include <ArduinoJson.h>
#include <StringHelper.h>
#include <string.h>
#include <SoftwareSerial.h>
#include <Outlet.h>

#define DEBUG       true
#define LED         13
#define CH_PD       8
#define BAUDRATE    115200
#define PIN_TX      7
#define PIN_RX      6

#define WIFI_IP     "192.168.0.10"
#define SERVER_API  "192.168.0.105"  // "http://www.mocky.io/v2/5db98c6b3000005a005ee41e" // "192.168.0.20"
#define SERVER_PORT "3000" // 80
#define ENDPOINT    "/status" //"/api/outlet/status"
#define N_RELAYS    2


char* PAYLOAD;
struct STATUS {
  unsigned char outlet;
  bool state;
};

Outlet relay1(2, false);
Outlet relay2(3, false);
STATUS relayStates[N_RELAYS];
SoftwareSerial WIFISerial(PIN_RX, PIN_TX);


void setup () {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(BAUDRATE);

  if (DEBUG) Serial.println("Trying to setup the relays...");
  relay1.begin();
  relay2.begin();
  if (DEBUG) Serial.println("Relays setup done!");

  setupWifi();
}

void loop () {

  if (connect(0, SERVER_API)) {
    bool isSent = sendRequest("GET", ENDPOINT, "", 0, SERVER_API);
    if (isSent) {
      bool parsed = parseStatus();
      if (DEBUG) Serial.println("Trying to parse the received data... " + (char)parsed);
      if (parsed) {
        updateRelays();
        if (DEBUG) printStatus();
      }
    } else {
        if (DEBUG) Serial.println("Request couldn't be sent...");
    }
    disconnect(0);

  } else {
      if (DEBUG) Serial.println("Connection to the server " + (String)SERVER_API + " failed!");
  }
}


/*
 * Open connection to the HTTP server
 * AT+CIPSTART=id,"type","addr",port
 * id = 0
 * type = "TCP"
 * addr = "www.example.com" | IP
 * port = 80
*/
bool connect(int connectionId, String server){
  String cipStart = "AT+CIPSTART=" + String(connectionId) + ",\"TCP\",\""+ server +"\"," + SERVER_PORT;
  WIFISerial.println(cipStart);
  if (DEBUG) Serial.println(cipStart);

  delay(1000);

  if(WIFISerial.available() > 0)
    if(WIFISerial.find("OK"))
      return true;

  return false;
}

/* Close connection to the HTTP server
 * AT+CIPCLOSE=0
 */
bool disconnect(int connectionId){
  String closeCmd = "AT+CIPCLOSE=" + String(connectionId);
  WIFISerial.println(closeCmd);
  if (DEBUG) Serial.println(closeCmd);
  delay(1000);

  if(WIFISerial.available() > 0){
    if(WIFISerial.find("CLOSED")){
      clearBuffer();
      return true;
    }
  }
  return false;
}


 /*
  * Send the HTTP GET or POST request to the server
  * GET /api/outlet/status HTTP1/1\r\n
  * Host: 192.168.1.20:80\r\n\r\n
  */
bool sendRequest(String method, String resource, String queryParams, int connectionId, String server) {
  bool isPost = false;

  String cipCmd = "";
  cipCmd += method + " " + resource + " HTTP/1.1\r\n";
  cipCmd += "Host: " + server + ":" + SERVER_PORT + "\r\n";
  cipCmd += "Content-Type: application/json\r\n"; // Skip to body

  if(method == "POST" && queryParams != NULL){
    cipCmd += "Content-Length: "+ String(queryParams.length()) +"\r\n";
    cipCmd += "Connection: close\r\n\r\n";
    cipCmd += queryParams; // add json query parameters to the request
    isPost = true;
  } else
    cipCmd += "Connection: close\r\n\r\n";

  String cipSend = "AT+CIPSEND=" + String(connectionId) + "," + cipCmd.length();
  WIFISerial.println(cipSend);
  if (DEBUG) Serial.println(cipSend);
  delay(1000); // wait until request is sent

  if(WIFISerial.available() > 0){
    if(WIFISerial.find("OK")){
      if(isPost){
        sendWifiCommand(cipCmd, 2000, true);
      }

      if (DEBUG) Serial.println("Requesting data from server...");
      sendHTTPCmd(cipCmd, 5000);
      if (DEBUG) Serial.println(cipCmd);
      return true;
    }
  }

  return false;
}

void clearBuffer(){
  while(WIFISerial.available()){
    char a = WIFISerial.read();
    if (DEBUG) Serial.write(a);
  }
}

void setupWifi(){
  WIFISerial.begin(BAUDRATE);

  pinMode(CH_PD, OUTPUT);
  digitalWrite(CH_PD, LOW);
  delay(10);
  digitalWrite(CH_PD, HIGH);

  if (DEBUG) Serial.println("Initializing Wi-Fi setup...");
  sendWifiCommand("AT+CIPSTA=\"" + (String)WIFI_IP + "\"\r\n",2000,DEBUG);
  sendWifiCommand("AT+CIFSR\r\n",3000,DEBUG); // get ip address
  sendWifiCommand("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendWifiCommand("AT+SLEEP=0\r\n",500,DEBUG);
  if (DEBUG) Serial.println("WIFI setup done!");
}

String sendWifiCommand(String command, const int timeout, boolean debug) {
    String response = "";
    long int time = millis();

    WIFISerial.print(command); // send the read character to the esp8266

    while ((time + timeout) > millis()) {
      while (WIFISerial.available()) {
        char c = WIFISerial.read(); // read the next character.
        response +=c;
      }
    }

    if (debug) Serial.print(response);
    return response;
}

/* Status format
{
  "data":
  [
    {
      "outlet": "1",
      "state": "1"
    },
    {
      "outlet": "2",
      "state": "0"
    }
  ]
}*/
bool parseStatus() {
  const size_t BUFFER_SIZE =
      JSON_OBJECT_SIZE(1)  // the root object has 1 element
    + JSON_OBJECT_SIZE(2)  // the "data" array has 2 array elements
    + JSON_OBJECT_SIZE(2)  // the array 1 has 2 elements
    + JSON_OBJECT_SIZE(2); // the array 2 has 2 elements

  StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(PAYLOAD);

  if (!root.success()) {
    return false;
  }

  for(int i = 0; i < N_RELAYS; i++) {
    String value = (root["data"][i]["outlet"]);
    relayStates[i].outlet = value.toInt();
    String str = (root["data"][i]["state"]);
    relayStates[i].state = (str == "1") ? true: false;
  }

  return true;
}

void printStatus() {
    Serial.println("\nStates for outlets: ");
    for(int i = 0; i < N_RELAYS; i++){
      Serial.print("\r\nOutlet: ");
      Serial.print(relayStates[i].outlet);
      Serial.print(" -- State: ");
      Serial.print((relayStates[i].state) == true ? "1": "0");
    }
}

void sendHTTPCmd(String command, const int timeout){

    if(DEBUG) Serial.println("Trying to get the payload");
    String response = sendWifiCommand(command, timeout, true);
    if(DEBUG) Serial.println("RESPONSE: " + response);

    String payload = getDataPayload(response);
    payload.trim();

    if(DEBUG) Serial.println("PAYLOAD: " + payload);

    if(payload != NULL){
      int payloadLength = payload.length() + 1;
      PAYLOAD = (char *)malloc(payloadLength * sizeof(char));

      payload.toCharArray(PAYLOAD, payloadLength);
    }
}

String getDataPayload(String httpRep) {
  int index = httpRep.indexOf('{');
  String str = "";
  str += httpRep.substring(index, httpRep.length());
  return str;
}

bool updateRelays() {
  if (DEBUG) Serial.println("Updating relays...");
  for(int i = 0; i < N_RELAYS; i++)
    updateRelay((char)relayStates[i].outlet, relayStates[i].state);
}

void updateRelay(char outlet, bool state) {
  switch(outlet) {
    case 1:
      if(state) relay1.turnOn(); else relay1.turnOff();
    break;
    case 2:
      if(state) relay2.turnOn(); else relay2.turnOff();
    break;
  }
}
