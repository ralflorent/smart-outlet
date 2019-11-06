#include <ArduinoJson.h>
#include <StringHelper.h>
#include <string.h>
#include <Outlet.h>

#define DEBUG       true
#define LED         13
#define CH_PD       50
#define BAUDRATE    115200

#define WIFI_IP     "192.168.0.10"
#define SERVER_API  "192.168.0.104"
#define SERVER_PORT "5000"
#define ENDPOINT    "/api/outlet/statusino"
#define N_RELAYS    2

#define WIFISerial Serial3 // software serial has a buffer overflow issue

char* PAYLOAD;
struct STATUS {
  unsigned char outlet;
  bool state;
};

Outlet relay1(52, false);
Outlet relay2(53, false);
STATUS relayStates[N_RELAYS];

void setup () {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(BAUDRATE);

  if (DEBUG) Serial.println("Trying to setup the relays...");
  relay1.begin();
  relay2.begin();
  for (int i = 0; i < N_RELAYS; i++) {
    relayStates[i].outlet = i + 1;
    relayStates[i].state = false;
  }
  if (DEBUG) Serial.println("Relays setup done!");

  setupWifi();
}

void loop () {

  if (connect(0, SERVER_API)) {
    bool isSent = sendRequest("GET", ENDPOINT, "", 0, SERVER_API);
    if (isSent) {
      if (DEBUG) Serial.println("Request has been sent successfully!");
      bool parsed = parseRelayStates();
      if (parsed) updateRelays();
    } else {
      if (DEBUG) Serial.println("Request couldn't be sent...");
    }
    disconnect(0);

  } else {
    if (DEBUG) Serial.println("Connection to the server " + String(SERVER_API) + " failed!");
  }
}


/*
   Open connection to the HTTP server
   AT+CIPSTART=id,"type","addr",port
   id = 0
   type = "TCP"
   addr = "www.example.com" | IP
   port = 80
*/
bool connect(int connectionId, String server) {
  String cipStart = "AT+CIPSTART=" + String(connectionId) + ",\"TCP\",\"" + server + "\"," + SERVER_PORT;
  WIFISerial.println(cipStart);
  if (DEBUG) Serial.println(cipStart);

  delay(500);

  if (WIFISerial.available())
    if (WIFISerial.find("OK"))
      return true;

  return false;
}

/* Close connection to the HTTP server
   AT+CIPCLOSE=0
*/
bool disconnect(int connectionId) {
  String closeCmd = "AT+CIPCLOSE=" + String(connectionId);
  WIFISerial.println(closeCmd);
  if (DEBUG) Serial.println(closeCmd);
  delay(500);

  if (WIFISerial.available() > 0) {
    if (WIFISerial.find("CLOSED")) {
      clearBuffer();
      return true;
    }
  }
  digitalWrite(LED, LOW);
//  relay1.turnOff();
  return false;
}


/*
   Send the HTTP GET or POST request to the server
   GET /api/outlet/status HTTP1/1\r\n
   Host: 192.168.1.20:80\r\n\r\n
*/
bool sendRequest(String method, String resource, String queryParams, int connectionId, String server) {
  bool isPost = false;

  // Prepare command to send http request
  String cipCmd = "";
  cipCmd += method + " " + resource + " HTTP/1.1\r\n";
  cipCmd += "Host: " + server + ":" + SERVER_PORT + "\r\n";
  cipCmd += "Content-Type: application/json\r\n";

  if (method == "POST" && queryParams != NULL) {
    cipCmd += "Content-Length: " + String(queryParams.length()) + "\r\n";
    cipCmd += "Connection: close\r\n\r\n";
    cipCmd += queryParams; // add json query parameters to the request
    isPost = true;
  } else {
    cipCmd += "Connection: close\r\n\r\n";
  }

  // First, establish an HTTP connection/session
  String cipSend = "AT+CIPSEND=" + String(connectionId) + "," + cipCmd.length();
  WIFISerial.println(cipSend);
  if (DEBUG) Serial.println(cipSend);
  delay(500); // wait until request is sent

  // Now try to send the HTTP request
  if (WIFISerial.available()) {
    if (WIFISerial.find("OK")) {
      if (isPost) {
        sendWifiCommand(cipCmd, 1000, DEBUG);
      } else {
        sendHTTPCmd(cipCmd, 1500, DEBUG); // wraps the sendWifiCommand with extra steps
      }
      if (DEBUG) Serial.println(cipCmd);
      return true;
    }
  }

  return false;
}

void clearBuffer() {
  while (WIFISerial.available()) {
    char a = WIFISerial.read();
    if (DEBUG) Serial.write(a);
  }
}

void setupWifi() {
  WIFISerial.begin(BAUDRATE);

  pinMode(CH_PD, OUTPUT);
  digitalWrite(CH_PD, LOW);
  delay(10);
  digitalWrite(CH_PD, HIGH);

  if (DEBUG) Serial.println("Initializing Wi-Fi setup...");
  sendWifiCommand("AT+CIPSTA=\"" + String(WIFI_IP) + "\"\r\n", 2000, DEBUG);
  sendWifiCommand("AT+CIFSR\r\n", 3000, DEBUG); // display ip address
  sendWifiCommand("AT+CIPMUX=1\r\n", 1000, DEBUG); // configure for multiple connections
  sendWifiCommand("AT+SLEEP=0\r\n", 500, DEBUG); // disable sleep mode
  if (DEBUG) Serial.println("WIFI setup done!");
}

String sendWifiCommand(String command, const int timeout, boolean debug) {

  String response = "";
  long int time = millis();

  WIFISerial.print(command); // send the read character to the esp8266

  while ((time + timeout) > millis()) {
    while (WIFISerial.available()) {
      // The esp has data so display its output to the serial window
      char c = WIFISerial.read(); // read the next character.
      response += c;
    }
  }

  if (debug) Serial.print(response);

  return response;
}

void sendHTTPCmd(String command, const int timeout, boolean debug) {

  String response = sendWifiCommand(command, timeout, debug);

  String payload = getDataPayload(response);
  payload.trim();

  if (payload != NULL) {
    int payloadLength = payload.length() + 1;
    PAYLOAD = (char *)malloc(payloadLength * sizeof(char));

    payload.toCharArray(PAYLOAD, payloadLength);
  }

  clearBuffer();
}

/*********************************************************************************/
/* Status format
  {
    "data": [
      {
        "outlet": 1,
        "state": 1
      },
      {
        "outlet": 2,
        "state": 0
      }
    ]
  }
*/
bool parseRelayStates() {
  // Buffer size
  const size_t BUFFER_SIZE =
    JSON_OBJECT_SIZE(1)  // the root object has 1 element
    + JSON_ARRAY_SIZE(2)  // the "data" array has 2 array elements
    + 2 * JSON_OBJECT_SIZE(2); // the array 1 has 2 elements

  StaticJsonDocument<BUFFER_SIZE> root;
  // Parse the JSON input
  DeserializationError err = deserializeJson(root, PAYLOAD);
  // Parse succeeded?
  if (err) {
    if (DEBUG) Serial.print(F("deserializeJson() returned "));
    if (DEBUG) Serial.println(err.c_str());
    return;
  }

  for (int i = 0; i < N_RELAYS; i++) {
    String value = (root["data"][i]["outlet"]);
    relayStates[i].outlet = value.toInt();
    String str = (root["data"][i]["state"]);
    relayStates[i].state = (str.toInt() == 1) ? true : false;
  }

  return true;
}

String getDataPayload(String httpRep) {
  int startIndex = httpRep.indexOf('{');
  int endIndex = httpRep.lastIndexOf('}');
  String str = "";
  str += httpRep.substring(startIndex, httpRep.length());
  return str;
}

bool updateRelays() {
  if (DEBUG) Serial.println("Updating relays...");
  for (int i = 0; i < N_RELAYS; i++)
    updateRelay((char)relayStates[i].outlet, relayStates[i].state);

  if (DEBUG) printStatus();
}

void updateRelay(char outlet, bool state) {
  switch (outlet) {
    case 1:
      if (state) relay1.turnOn(); else relay1.turnOff();
      break;
    case 2:
      if (state) relay2.turnOn(); else relay2.turnOff();
      break;
  }
}

void printStatus() {
  Serial.println("\nStates for outlets: ");
  for (int i = 0; i < N_RELAYS; i++) {
    Serial.print("\r\n==> Outlet: ");
    Serial.print(relayStates[i].outlet);
    Serial.print(" -- State: ");
    Serial.print((relayStates[i].state) == true ? "1" : "0");
    Serial.print("\r\n");
  }
}