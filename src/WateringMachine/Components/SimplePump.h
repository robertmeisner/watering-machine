/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/

#ifndef SimplePumps_h
#include "StateMachineInterfaces/PumpStateMachine.h"
#define SimplePumps_h

class SimplePump : public PumpStateMachine
{
public:
  SimplePump(bool (*startFunc)(), bool (*stopFunc)(), bool (*initFunc)() = nullptr);

  bool start();
  bool stop();
  unsigned long getDurationSinceLastChange();
  bool init();
  bool tick(){};

protected:
  bool (*_startFunc)();
  bool (*_stopFunc)();
  bool (*_initFunc)();
  unsigned long sinceLastChangeChrono;
};

#endif