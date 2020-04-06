/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/

#ifndef PulsePump_h
#include "SimplePump.h"
#define PulsePump_h

class PulsePump : public SimplePump
{
public:
    PulsePump(bool (*startFunc)(), bool (*stopFunc)(), bool (*initFunc)() = nullptr);
    bool start();
    bool tick();

protected:
    bool pulse();
    bool pulsePause();
    bool isPulsing = false;
    unsigned lastPulseChange = 0;
    unsigned long pulseDuration = 1000 * 10;
    unsigned long pulseInterval = 1000 * 3;
};

#endif