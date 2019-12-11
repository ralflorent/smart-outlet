#include <SoftwareSerial.h>

#define DEBUG       true
#define LED         13
#define BAUDRATE    115200

short pinTx = 7; // use pin 7 as Arduino TX pin
short pinRx = 6; // use pin 6 as Arduino RX pin
SoftwareSerial WIFISerial(pinRx, pinTx);

void setup () {
  WIFISerial.begin(BAUDRATE);
  Serial.begin(BAUDRATE);
  pinMode(LED, OUTPUT);

  if (DEBUG) Serial.println("Initializing Wi-Fi Setup...");

  // send command to the ESP (see datasheets for more details)
  sendWifiCommand("AT+RST\r\n", 1000, DEBUG); // reset module
  sendWifiCommand("AT+CWLAP\r\n", 2000, DEBUG); // List of access points
  sendWifiCommand("AT+CWQAP\r\n", 2000, DEBUG);

  sendWifiCommand("AT+CWJAP=\"Network_SSID\",\"its-password\"\r\n", 5000, DEBUG); // Set connection to Access Point
  sendWifiCommand("AT+CIPSTA=\"192.168.0.10\"\r\n", 2000, DEBUG); // Set static IP

  sendWifiCommand("AT+CWMODE=3\r\n", 1000, DEBUG); // Activate multi(plex) connection mode
  sendWifiCommand("AT+CIFSR\r\n", 1000, DEBUG); // Display IP address

  if (DEBUG)  Serial.println("Wi-Fi Setup done");
}

void loop () {

}

String sendWifiCommand(String command, const int timeout, boolean debug) {
    String response = "";
    long int time = millis();

    WIFISerial.print(command); // send the read character to the esp8266

    while ((time + timeout) > millis()) {
      while (WIFISerial.available()) {
        // The ESP has data so display its output to the serial window
        char c = WIFISerial.read(); // read the next character.
        response +=c;
      }
    }

    if (debug) {
      Serial.print(response);
    }
    return response;
}
