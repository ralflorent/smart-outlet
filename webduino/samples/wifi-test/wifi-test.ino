#include <ArduinoJson.h>
#include <StringHelper.h>
#include <string.h>
#include <SoftwareSerial.h>

#define DEBUG       false
#define LED         13
#define CH_PD       8
#define BAUDRATE    115200
#define PIN_TX      7
#define PIN_RX      6
#define _SS_MAX_RX_BUFF 256 // RX buffer size

#define WIFI_IP     "192.168.0.10"
#define SERVER_API  "192.168.0.105"  // "http://www.mocky.io/v2/5db98c6b3000005a005ee41e" // "192.168.0.20"
#define SERVER_PORT "3000" // 80
#define ENDPOINT    "/status" //"/api/outlet/status"
#define N_RELAYS    2

// SoftwareSerial WIFISerial(PIN_RX, PIN_TX);
#define WIFISerial Serial

void setup () {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  Serial.begin(BAUDRATE);

  setupWifi();
}

void loop () {

  if (connect(0, SERVER_API)) {
    bool isSent = sendRequest("GET", ENDPOINT, "", 0, SERVER_API);
    if (isSent) {
      if (DEBUG) Serial.println("Request has been sent successfully!");
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

  delay(1000);

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
  delay(1000);

  if (WIFISerial.available() > 0) {
    if (WIFISerial.find("CLOSED")) {
      clearBuffer();
      return true;
    }
  }
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
  delay(1000); // wait until request is sent

  // Now try to send the HTTP request
  if (WIFISerial.available()) {
    if (WIFISerial.find("OK")) {
      if (isPost) {
        sendWifiCommand(cipCmd, 1000, DEBUG);
      } else {
        sendWifiCommand(cipCmd, 1000, DEBUG);
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

//    long int time = millis();
//    char espBuffer[1024] = {0};
//    int readCount = 0;
//
//    WIFISerial.println(command); // send the read character to the esp8266
//
//    while ((time + timeout) > millis()) {
//      if (WIFISerial.overflow()) Serial.println("SoftwareSerial overflow!");
//      if (WIFISerial.available() > readCount + sizeof espBuffer - 1)
//          break;
//      readCount += WIFISerial.readBytes(espBuffer + readCount, WIFISerial.available());
//    }
//
//    if (debug) Serial.print(espBuffer);
//    return espBuffer;

  String response = "";
  long int time = millis();

  WIFISerial.print(command); // send the read character to the esp8266

  while ((time + timeout) > millis()) {
    while (WIFISerial.available()) {
      if(WIFISerial.find("data")) digitalWrite(LED, LOW);
      // The esp has data so display its output to the serial window
      char c = WIFISerial.read(); // read the next character.
      response += c;
    }
  }

  if (debug) Serial.print(response);

  return response;
}
