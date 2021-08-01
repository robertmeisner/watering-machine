/*
  MoistureSensor.h - Water Level Sensor
  Created by Robert Meisner, 30th July 2021.
  Released into the public domain.
*/
#include "StateMachineInterfaces/StateMachine.h"

#ifndef WaterLevelSensor_h
#define WaterLevelSensor_h
#define WATER_LEVEL_READINGS_COUNT 3
enum WaterLevelSensorStates
{
  STATE_WLS_READING,
  STATE_WLS_IDLE
};
enum WaterLevelSensorCommand
{
  COMMAND_WLS_READ,
  COMMAND_WLS_FINISHED_READ
};
/**
 * Moisture sensor allows you to read single moisture level or mean value of last 8 readings.
 */
class WaterLevelSensor : StateMachine
{
public:
  /**
   * MoistureSensor constructor
   * 
   * @param  {float} readFunc() : function used to perform single moisture reading
   * @param  {bool} initFunc()  : function used to inititalize the sensor.
   */
  WaterLevelSensor(float readFunc(), bool initFunc() = nullptr);
  /**
   * Reads water level using provided readFunc() and returns single Water Level reading.
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
  WaterLevelSensorStates state = WaterLevelSensorStates::STATE_WLS_IDLE;
  float (*_readFunc)();
  bool (*_initFunc)();
  int _levelReadingNumber = 0;
  float _levelReadings[WATER_LEVEL_READINGS_COUNT];
  int nextState(int command);
};

#endif