String httpget(String request) {
  String response="";

  // webUI specific pages

  if (request.indexOf("/powerOn")>=0) { doPowerOn(); }

  else if (request.indexOf("/standbyOn")>=0) { doStandbyOn(); }

  else if (request.indexOf("/volumeUp")>=0) { doVolumeUp(); }

  else if (request.indexOf("/volumeDown")>=0) { doVolumeDown(); }

  else if (request.indexOf("/volume")>=0) {
    int a=request.indexOf(",")+1;
    doVolume(request.substring(a).toInt()); }

  else if (request.indexOf("/source")>=0) {
    int a=request.indexOf(",")+1;
    doSource(request.substring(a).toInt()); }

  else if (request.indexOf("/getState")>=0) {
    response+=String(currentPow) + "," + String(currentVol) + "," + String(currentSrc); }

  // WLAN Choose specific pages

  else if (request.indexOf("/appName")>=0) {
    response+=String(appName) + ",";
    response+=String(appDesc) + ","; }

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (wlanConfig.statusStation) { response="<div class=\"x1\">WLAN AP " + wlanConfig.ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) {
    if (WiFi.softAPgetStationNum()==0) { response=a2h(wlanConfig.ssidStation) + "," + a2h(wlanConfig.passwordStation) + ","; }
    else { response=a2h(wlanConfig.ssidStation) + ",,"; } }

  else if (request.indexOf("/scanAP")>=0) {
    wlanTimer=millis()+20000; int indexes=WiFi.scanNetworks(); response+="<div class=\"x1\"><table>"; for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<tr><td onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</td></tr>"; } } response+="</table></div>"; }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    if (!wlanConfig.statusStation || WiFi.softAPgetStationNum()==0) {
      wlanConfig.ssidStation=h2a(request.substring(a,b-1)); wlanConfig.passwordStation=h2a(request.substring(b)); wlanConfig.reconnectCount=0; reconnectWLAN(); }
    else { if (debug) { Serial.println("WLAN Station reconnect prevented."); } } }

  // Default page

  else if (request.indexOf("/favicon.ico")>=0) { }

  else { response=index_html; }

  return response; }
