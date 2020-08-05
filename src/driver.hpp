#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "Arduino.h"
#include "Wire.h" // I2C

// Define reference voltage
#define V_REF 5.0
#define SLOW_SPEED 3.7
#define MEDIUM_SPEED 4.5
#define FAST_SPEED 4.99

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0.
#define MCP4725_ADDR 0x60

class Driver {
public:
   Driver(int fr_toggle_pin, int l_turn_pin, int r_turn_pin, int lr_enable_pin);
   void forward(float speed = MEDIUM_SPEED);
   void reverse(float speed = MEDIUM_SPEED);
   void brake();
   void turnLeft();
   void turnRight();
   void straight();

private:
   void updateDAC(float voltage);
   int voltToInputCode(float voltage);
   void transmitToDAC(int code);

   int m_fr_toggle_pin, m_l_turn_pin, m_r_turn_pin, m_lr_enable_pin;

};

#endif
