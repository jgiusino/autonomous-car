#include <Arduino.h>
#include "sensor.hpp"
#include "driver.hpp"

#define LR_ENABLE 7
#define L_TURN 6
#define R_TURN 5
#define FR_TOGGLE 3

#define TRIGGER_PIN 12
#define ECHO_PIN 11

//String input; // string to store input
//boolean serialNeedsUpdate = false;

SR04 sensor(TRIGGER_PIN,ECHO_PIN);
Driver driver(FR_TOGGLE,L_TURN, R_TURN, LR_ENABLE);

long timer;
bool isCoasting = false;

void setup()
{
   //Serial.begin(9600);
   //Serial.setTimeout(5000);
   driver.brake();
   driver.straight();
}

void loop()
{
   //Serial.print(dist);Serial.print("\n");
   if(sensor.avgDistance() < 20) {
      driver.brake();
      isCoasting = false; // no longer coasting
      driver.reverse();
      driver.turnLeft();
      while(sensor.avgDistance() < 20);
      driver.brake();
      driver.turnRight();
      driver.forward();
      timer = millis();
   }
   else {
      driver.straight();
   }
   // slows car down so it doesn't plunge into anything
   if(millis() - timer > 1500 && !isCoasting) {
      driver.forward(SLOW_SPEED);
      isCoasting = true; // now coasting
   }
}
