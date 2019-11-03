#include <ArduinoJson.h>
#include <StringHelper.h>
#include <string.h>
#include <Outlet.h>

#define DEBUG       true
#define LED         13
#define BAUDRATE    115200
#define N_RELAYS    2

const String DATA = "fsadfasduuwi8439isdj { \"data\": [ { \"outlet\": \"1\", \"state\": \"1\" }, { \"outlet\": \"2\", \"state\": \"1\" } ] }";

char* PAYLOAD;
struct STATUS {
  unsigned char outlet;
  bool state;
};

Outlet relay1(2, false);
Outlet relay2(3, false);
STATUS relayStates[N_RELAYS];

void setup() {
  // put your setup code here, to run once:
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
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()) {
    String c = Serial.readString();

    String payload = getDataPayload(DATA);
    payload.trim();
  
    if (DEBUG) Serial.println("PAYLOAD: " + payload);
  
    if (payload != NULL) {
      int payloadLength = payload.length() + 1;
      PAYLOAD = (char *)malloc(payloadLength * sizeof(char));
  
      payload.toCharArray(PAYLOAD, payloadLength);
    }
    
     bool parsed = parseRelayStates();
     if (parsed) { 
      updateRelays();
      printStatus();
     }
  }
  
}

bool parseRelayStates() {
  if (DEBUG) Serial.println("Trying to parse...");
  const size_t BUFFER_SIZE =
    JSON_OBJECT_SIZE(1)  // the root object has 1 element
    + JSON_OBJECT_SIZE(2)  // the "data" array has 2 array elements
    + JSON_OBJECT_SIZE(2)  // the array 1 has 2 elements
    + JSON_OBJECT_SIZE(2); // the array 2 has 2 elements

  StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(PAYLOAD);

  if (!root.success()) {
    if (DEBUG) Serial.println("Parsing failed...");
    return false;
  }

  for (int i = 0; i < N_RELAYS; i++) {
    String value = (root["data"][i]["outlet"]);
    relayStates[i].outlet = value.toInt();
    String str = (root["data"][i]["state"]);
    relayStates[i].state = (str == "1") ? true : false;
  }

  return true;
}

String getDataPayload(String httpRep) {
  int startIndex = httpRep.indexOf('{');
  int endIndex = httpRep.lastIndexOf('}');
  String str = "";
  str += httpRep.substring(startIndex, endIndex + 1);
  return str;
}

bool updateRelays() {
  if (DEBUG) Serial.println("Updating relays...");
  for (int i = 0; i < N_RELAYS; i++)
    updateRelay((char)relayStates[i].outlet, relayStates[i].state);
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
