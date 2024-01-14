const char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>teacRC</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/teacRC">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#f0f0f0; color:#000000; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a   { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1b   { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
.but   { background-color:#f0f0f0; padding:0.1em 0.4em; }
</style>
<script>

function webUIinit() {
  currentPow=false; currentVol=0; muteVol=0; currentSrc=0;
  red="#E09090"; green="#90E090"; yellow="#FFE460"; gray="#e0e0e0"; darkgray="#d0d0d0"; blue="#c2d5ed";
  appName="&nbsp;"; appDesc="&nbsp;"; ajaxObj=[]; requestAJAX('appName'); setStateTimer(true); }

function doDisplay() {
  if (currentPow) { id("powerBut").style.backgroundColor=green; }
  else { id("powerBut").style.backgroundColor=red; }
  id("volumeBut").innerHTML="Volume "+currentVol;
  if (currentVol && currentPow) { id("volumeBut").style.backgroundColor=darkgray; }
  else { id("volumeBut").style.backgroundColor=gray; }
  for (i=0;i<6;i++) { if (i==currentSrc && currentPow) { id("sourceBut"+i).style.backgroundColor=darkgray; }
    else { id("sourceBut"+i).style.backgroundColor=gray; } } }

function doPowerOn() { requestAJAX('powerOn'); setStateTimer(false); currentPow=true; currentVol=3; muteVol=0; doDisplay(); }
function doStandbyOn() { requestAJAX('standbyOn'); setStateTimer(false); currentPow=false; currentVol=0; muteVol=0; doDisplay(); }
function doVolume(value) { if (currentPow) { requestAJAX('volume,'+value); setStateTimer(false); currentVol=value; doDisplay(); } }
function doVolumeUp() { if (currentPow) { requestAJAX('volumeUp'); setStateTimer(false); currentVol++; muteVol=0; doDisplay(); } }
function doVolumeDown() { if (currentPow && currentVol) { requestAJAX('volumeDown'); setStateTimer(false); currentVol--; muteVol=0; doDisplay(); } }
function doVolumeMute() { if (currentPow) { if (muteVol) { doVolume(muteVol); muteVol=0; } else { muteVol=currentVol; doVolume(0); } } }
function doSource(value) { if (currentPow) { requestAJAX('source,'+value); setStateTimer(false); currentSrc=value; doDisplay(); } }

function setStateTimer(now) { clearStateTimer(); statusTimer=window.setInterval("getState();",10000); if (now) { getState(); } }
function clearStateTimer() { if (typeof statusTimer!=='undefined' ) { window.clearInterval(statusTimer); ajaxObj["getState"].abort(); } }
function getState() { requestAJAX('getState'); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="appName") {
      id("appName").innerHTML=event.target.responseText.split(",")[0];
      id("appDesc").innerHTML=event.target.responseText.split(",")[1]; }
    else if (event.target.url=="getState") {
      currentPow=event.target.responseText.split(",")[0]*1; currentVol=event.target.responseText.split(",")[1]*1;
      currentSrc=event.target.responseText.split(",")[2]*1; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a" id="appName">&nbsp;</div></div>
<div><div class="x0b" id="appDesc">&nbsp;</div></div>

<div><div class="x1b" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x3" id="powerBut">Power</div>
     <div class="x3" onclick="doPowerOn();"><span class="but">&nbsp;&nbsp;&nbsp;On&nbsp;&nbsp;&nbsp;</span></div>
     <div class="x3" onclick="doStandbyOn();"><span class="but">Standby</span></div></div>
<div><div class="x3" id="sourceBut0" onclick="doSource(0);">MD</div>
     <div class="x3" id="sourceBut1" onclick="doSource(1);">Tape</div>
     <div class="x3" id="sourceBut2" onclick="doSource(2);">CD</div></div>
<div><div class="x3" id="sourceBut3" onclick="doSource(3);">Tuner</div>
     <div class="x3" id="sourceBut4" onclick="doSource(4);">Phono</div>
     <div class="x3" id="sourceBut5" onclick="doSource(5);">Aux</div></div>
<div><div class="x3" id="volumeBut" onclick="doVolumeMute();">&nbsp;</div>
     <div class="x3" onclick="doVolumeDown();"><span class="but">&nbsp;&nbsp;&#8722;&nbsp;&nbsp;</span></div>
     <div class="x3" onclick="doVolumeUp();"><span class="but">&nbsp;&nbsp;+&nbsp;&nbsp;</span></div></div>
</div>

</body></html>

)";
