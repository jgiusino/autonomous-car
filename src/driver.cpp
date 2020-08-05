#include "driver.hpp"

Driver::Driver(int fr_toggle_pin, int l_turn_pin, int r_turn_pin, int lr_enable_pin) {
   m_fr_toggle_pin = fr_toggle_pin;
   m_l_turn_pin = l_turn_pin;
   m_r_turn_pin = r_turn_pin;
   m_lr_enable_pin = lr_enable_pin;

   Wire.begin();
   pinMode(m_fr_toggle_pin,OUTPUT);
   pinMode(m_l_turn_pin, OUTPUT);
   pinMode(m_r_turn_pin, OUTPUT);
   pinMode(m_lr_enable_pin, OUTPUT);
}

void Driver::forward(float speed) {
   digitalWrite(m_fr_toggle_pin, LOW);
   updateDAC(FAST_SPEED);
   delay(250);
   updateDAC(speed);
}

void Driver::reverse(float speed) {
   digitalWrite(m_fr_toggle_pin, HIGH);
   updateDAC(FAST_SPEED);
   delay(250);
   updateDAC(speed);
}

void Driver::brake() {
   updateDAC(0.0);
   delay(250);
}

void Driver::turnLeft() {
   digitalWrite(m_l_turn_pin,HIGH);
   digitalWrite(m_r_turn_pin, LOW);
   digitalWrite(m_lr_enable_pin, HIGH);
}

void Driver::turnRight() {
   digitalWrite(m_l_turn_pin,LOW);
   digitalWrite(m_r_turn_pin, HIGH);
   digitalWrite(m_lr_enable_pin, HIGH);
}

void Driver::straight() {
   digitalWrite(m_l_turn_pin,LOW);
   digitalWrite(m_r_turn_pin, LOW);
   digitalWrite(m_lr_enable_pin, LOW);
}

void Driver::updateDAC(float voltage) {
   if(voltage > V_REF || voltage < 0){
      Serial.println("ERROR: Invalid voltage");
   } else {
      int code = voltToInputCode(voltage);
      transmitToDAC(code);
   }
}

int Driver::voltToInputCode(float voltage) {
   return (int)(voltage*4096/V_REF);
}

void Driver::transmitToDAC(int code) {
   Wire.beginTransmission(MCP4725_ADDR);
   Wire.write(64);                     // cmd to update the DAC
   Wire.write(code >> 4);        // the 8 most significant bits...
   Wire.write((code & 15) << 4); // the 4 least significant bits...
   Wire.endTransmission();
   Serial.print(code, DEC);
   Serial.println(" transmitted to DAC.");
}
