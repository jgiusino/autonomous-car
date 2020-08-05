#if !defined(SENSOR_H)
#define SENSOR_H

#include "Arduino.h"

#define PULSE_TIMEOUT = 150000L
#define DEFAULT_DELAY 10
#define DEFAULT_PINGS 5

class SR04 {
public:
    SR04(int trigger_pin, int echo_pin);

    long distance();

    long avgDistance(int count=DEFAULT_PINGS);

    void ping();

    long getDistance();

private:
    long microsecondsToCentimeters(long duration);
    void triggerPulse();

    int m_trigger_pin, m_echo_pin;
    long m_current_distance;
    long m_duration, m_distance;
    bool m_auto_mode;
};
#endif // SENSOR_H
