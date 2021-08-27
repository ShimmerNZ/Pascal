#include <PololuMaestro.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial maestroSerial(8, 9);
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
MicroMaestro maestro(maestroSerial);
const int MOTION_PIN = 2;
long randNumber;

void setup()
{
  maestroSerial.begin(9600);
  mySoftwareSerial.begin(9600);
  randomSeed(analogRead(0));
  Serial.begin(115200);
  pinMode(MOTION_PIN, INPUT_PULLUP);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(1);  //Set volume value. From 0 to 30
  myDFPlayer.EQ(5);
  myDFPlayer.play(1);  //Play the first mp3

}

void loop()
{
  int proximity = digitalRead(MOTION_PIN);

  if (proximity == LOW) // If the sensor's output goes low, motion is detected
  {
    randomSeed(analogRead(0));
    randNumber = random(4);
    Serial.println(randNumber);
    if (randNumber == 0)
    {
      Serial.println(F("Starting Caw1"));
      maestro.restartScript(3);
      myDFPlayer.play(3);
      myDFPlayer.volume(10);
      myDFPlayer.start();
      delay(6000);
  Serial.println(myDFPlayer.readState()); //read mp3 state
  Serial.println(myDFPlayer.readVolume()); //read current volume
  Serial.println(myDFPlayer.readEQ()); //read EQ setting
  Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
  Serial.println(myDFPlayer.readFileCountsInFolder(3)); //read fill counts in folder SD:/03
    }
    if (randNumber == 1)
    {
      Serial.println(F("Starting Large Flap"));
      maestro.restartScript(2);
      delay(1000);
      myDFPlayer.play(2);
      delay(10000);

    }                                                   

    if (randNumber > 0)
    {
      Serial.println(F("Starting Flap"));
      maestro.restartScript(1);
      delay(10000);
    }

  }

}                                          
