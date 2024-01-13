#include <IRremoteESP8266.h>
#include <IRsend.h>

#define powerOn 0xA156E916     // Power On     - NEC - address = 0x6A85; - command = 0x97; - data = 0xA156E916;
#define standbyOn 0xA156C936   // Standby      - NEC - address = 0x6A85; - command = 0x93; - data = 0xA156C936;
#define sourceMD 0xA15629D6    // Source MD    - NEC - address = 0x6A85; - command = 0x94; - data = 0xA15629D6;
#define sourceTape 0xA156A956  // Source Tape  - NEC - address = 0x6A85; - command = 0x95; - data = 0xA156A956;
#define sourceCD 0xA15631CE    // Source CD    - NEC - address = 0x6A85; - command = 0x8C; - data = 0xA15631CE;
#define sourceTuner 0xA1568976 // Source Tuner - NEC - address = 0x6A85; - command = 0x91; - data = 0xA1568976;
#define sourcePhono 0xA156B14E // Source Phono - NEC - address = 0x6A85; - command = 0x8d; - data = 0xA156B14E;
#define sourceAux 0xA15624DB   // Source Aux   - NEC - address = 0x6A85; - command = 0x24; - data = 0xA15624DB;
#define volumeUp 0xA156F906    // Volume Up    - NEC - address = 0x6A85; - command = 0x9F; - data = 0xA156F906;
#define volumeDown 0xA1567986  // Volume Down  - NEC - address = 0x6A85; - command = 0x9E; - data = 0xA1567986;

IRsend irsend(17);
int currentVol=0;
int defaultVol=3;
bool currentPow=false;
int currentSrc=2;

void initRC711() { irsend.begin(); }

void doSource(int newSource) {
  switch(newSource) {
    case 0: irsend.sendNEC(sourceMD); delay(300); currentSrc=newSource; break;
    case 1: irsend.sendNEC(sourceTape); delay(300); currentSrc=newSource; break;
    case 2: irsend.sendNEC(sourceCD); delay(300); currentSrc=newSource; break;
    case 3: irsend.sendNEC(sourceTuner); delay(300); currentSrc=newSource; break;
    case 4: irsend.sendNEC(sourcePhono); delay(300); currentSrc=newSource; break;
    case 5: irsend.sendNEC(sourceAux); delay(300); currentSrc=newSource; break;
    default: break; } }

void doVolume(int newVolume) {
  while (currentVol<newVolume) { irsend.sendNEC(volumeUp); delay(300); currentVol++; }
  while (currentVol>newVolume) { irsend.sendNEC(volumeDown); delay(300); currentVol--; } }

void doPowerOn() {
  currentPow=true;
  irsend.sendNEC(powerOn); delay(300);
  doSource(currentSrc);
  doVolume(defaultVol); }

void doStandbyOn() {
  doVolume(0);
  currentPow=false;
  irsend.sendNEC(standbyOn); delay(300); }

void doVolumeUp() {
  doVolume(currentVol+1); }

void doVolumeDown() {
  doVolume(currentVol-1); }
