#pragma config(Sensor, S1,     DIMC,           sensorEV3_GenericI2C)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "hitechnic-compass.h"

task main () {
  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "Compass");
  displayCenteredTextLine(3, "Test 1");
  displayTextLine(5, "Press enter");
  displayTextLine(6, "to set target");
  sleep(2000);
  eraseDisplay();
  tHTMC compass;
  initSensor(&compass, S1);
  time1[T1] = 0;
  while(true) {
    if (time1[T1] > 1000) {
      eraseDisplay();
      displayTextLine(1, "Changing");
      displayTextLine(2, "target");
      sleep(500);
      readSensor(&compass);
      compass.offset = compass.heading;
      playSound(soundBlip);
      while(bSoundActive) sleep(1);
      time1[T1] = 0;
    }
    while(!getXbuttonValue(xButtonEnter)) {
      readSensor(&compass);
      eraseDisplay();
      displayTextLine(1, "Reading");
      displayTextLine(2, "Target: %4d", compass.offset);
      displayTextLine(4, "Abs:   %4d", compass.heading);
      displayTextLine(5, "Rel:   %4d", compass.relativeHeading);
      displayTextLine(6, "Press enter");
      displayTextLine(7, "to set target");
      sleep(100);
    }
  }
}
