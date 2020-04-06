/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/

#ifndef MechanicalButton_h
#define MechanicalButton_h
#include "StateMachineInterfaces/ButtonStateMachine.h"
#include <Arduino.h>

class MechanicalButton : public ButtonStateMachine
{
public:
  MechanicalButton(int pin, ButtonModes mode=ButtonModes::MODE_PULLDOWN);
  int buttonMode = ButtonModes::MODE_PULLDOWN;
  void setupInterruptHandler(uint8_t irq_pin, void (*interruptFunction)(void), int value);
  void handleInterrupt(void);
  bool init();
  bool tick();
private:
  uint8_t _pin;
  int nextState(int p);
};


#endif