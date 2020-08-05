#include "sensor.hpp"

SR04::SR04(int trigger_pin, int echo_pin) {
    m_trigger_pin = trigger_pin;
    m_echo_pin = echo_pin;
    pinMode(m_echo_pin,INPUT);
    pinMode(m_trigger_pin,OUTPUT);
    m_auto_mode = false;
    m_distance = 1;
}

long SR04::distance() {
    long result = 0;
    m_duration = 0;
    triggerPulse();
    m_duration = pulseIn(m_echo_pin,HIGH,150000L);
    result = microsecondsToCentimeters(m_duration);
    delay(25);
    return result;
}

long SR04::avgDistance(int count) {
    long average = 0;
    long result;
    long min = 1000;
    long max = 0;

    for(int i = 0; i < count + 2; i++) {
        result = distance();
        if(result > max) {
            max = result;
        }
        if(result < min) {
            min = result;
        }
        average += result;
    }
    average -= (max + min);
    return average/count;
}

void SR04::ping() {
    m_distance = distance();
}

long SR04::getDistance() {
    return m_distance;
}

void SR04::triggerPulse() {
    digitalWrite(m_trigger_pin,LOW);
    delayMicroseconds(2);
    digitalWrite(m_trigger_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigger_pin,LOW);
    delayMicroseconds(2);
}

long SR04::microsecondsToCentimeters(long duration) {
    long result = (duration * 100) / 14800;
    return result;
}
