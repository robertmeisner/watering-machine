/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#ifndef SimpleSwitch_h
#include "StateMachineInterfaces/SwitchStateMachine.h"
#define SimpleSwitch_h

class SimpleSwitch : public SwitchStateMachine
{
public:
  SimpleSwitch(bool onFunc(), bool offFunc(), bool initFunc() = nullptr);
  bool init();
  bool tick(){};
  bool turnOn();
  bool turnOff();

protected:
  bool (*_onFunc)();
  bool (*_offFunc)();
  bool (*_initFunc)();
};

#endif