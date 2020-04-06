/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#include "StateMachineInterfaces/StateMachine.h"

#ifndef MoistureSensor_h
#define MoistureSensor_h
#define MOISTURE_READINGS_COUNT 8
#define MOISTURE_READINGS_
enum MoistureSensorStates
{
  STATE_READING,
  STATE_IDLE
};
enum MoistureSensorCommand
{
  COMMAND_READ,
  COMMAND_FINISHED_READ
};

class MoistureSensor : StateMachine
{
public:
  MoistureSensor(float readFunc(), bool initFunc() = nullptr);

  float read();
  float readAvg();
  bool init();
  bool tick();

protected:
  MoistureSensorStates state = MoistureSensorStates::STATE_IDLE;
  float (*_readFunc)();
  bool (*_initFunc)();
  int _moistureReadingNumber = 0;
  float _moistureReadings[MOISTURE_READINGS_COUNT];
  int nextState(int command);
};

#endif