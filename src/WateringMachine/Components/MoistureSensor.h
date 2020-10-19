/*
  MoistureSensor.h - Library for flashing Morse code.
  Created by Robert Meisner, November 2, 2007.
  Released into the public domain.
*/
#include "StateMachineInterfaces/StateMachine.h"

#ifndef MoistureSensor_h
#define MoistureSensor_h
#define MOISTURE_READINGS_COUNT 8
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
/**
 * Moisture sensor allows you to read single moisture level or mean value of last 8 readings.
 */
class MoistureSensor : StateMachine
{
public:
  /**
   * MoistureSensor constructor
   * 
   * @param  {float} readFunc() : function used to perform single moisture reading
   * @param  {bool} initFunc()  : function used to inititalize the sensor.
   */
  MoistureSensor(float readFunc(), bool initFunc() = nullptr);
  /**
   * Reads moisture using rovided_readFunc() and returns single Moisture reading.
   * @return {float}  : last single Moisture reading;
   */
  float read();
  /**
   * reads a moisture level and returns mean value of last MOISTURE_READINGS_COUNT moisture readings.
   * @return {float}  : Mean value of last 8 readings
   */
  float readAvg();
   /**
   *  returns mean value of last MOISTURE_READINGS_COUNT moisture readings.
   * @return {float}  : Mean value of last 8 readings
   */
  float getAvg();
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