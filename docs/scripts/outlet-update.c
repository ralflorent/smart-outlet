// Omit previous scripts (imports, setup, global variables, etc.)
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
// Omit other scripts (helpers)