boolean debug=true;

const char* appName="teacRC";
const char* appDesc="TEAC A-H500 Remote Control";

#include "RC711.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initRC711();
  initWLAN();
  initDNS();
  initHTTP(); }

void loop() { wlanWorker(); dnsWorker(); httpWorker(); }
