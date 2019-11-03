#include <string.h>
#include <Outlet.h>

#define DEBUG       true
#define LED         13
#define CH_PD       8
#define BAUDRATE    115200
#define N_RELAYS    2

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
  String payload = "";
  while (Serial.available()) {
    payload = Serial.readString();
  }

  payload.trim();

  if (payload.length() > 0) {
    parseRelayStates(payload);
    updateRelays();
    printStatus();
  }
}

void parseRelayStates(String payload) {
  int index = String(payload.charAt(0)).toInt() - 1; // this integer parsing logic can be improved
  int outlet = String(payload.charAt(0)).toInt(); 
  bool state = (String(payload.charAt(1)).toInt() == 1) ? true : false;

  relayStates[index].outlet = outlet;
  relayStates[index].state = state;
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
