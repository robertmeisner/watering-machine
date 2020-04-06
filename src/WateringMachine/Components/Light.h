/*
  Created by Robert Meisner, 2020.
  Released into the public domain.
*/
#ifndef Light_h
#include "SimpleSwitch.h"
#define Light_h 

class Light : public SimpleSwitch
{
public:
    Light(bool onFunc(),bool offFunc(),bool initFunc()=nullptr);
    bool init();
    bool turnOn();
    bool turnOff();
    bool isOn();
    unsigned long getDurationSinceLastChange();
    SwitchStates state = SwitchStates::SWITCH_OFF;

private:
    unsigned long sinceLastChangeChrono;
    bool restartTimer();
};

#endif
