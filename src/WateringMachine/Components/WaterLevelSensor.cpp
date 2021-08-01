#include "WaterLevelSensor.h"
#include "../Utils/CustomLog.h"
bool wlcMockFunc()
{
  return true;
}
WaterLevelSensor::WaterLevelSensor(float readFunc(), bool initFunc())
{
  this->_readFunc = readFunc;
  if (initFunc != nullptr)
    this->_initFunc = initFunc;
  else
    this->_initFunc = wlcMockFunc;
}
float WaterLevelSensor::read()
{

  if (this->nextState(WaterLevelSensorCommand::COMMAND_WLS_READ) == WaterLevelSensorStates::STATE_WLS_READING)
  {
    float value = 0;

    this->_levelReadingNumber++;
    value = this->_readFunc(); // Read analog value

    this->_levelReadings[this->_levelReadingNumber - 1] = value;

    if (this->_levelReadingNumber > ( WATER_LEVEL_READINGS_COUNT-1))
    {
      this->_levelReadingNumber = 0;
    }
    this->nextState(WaterLevelSensorCommand::COMMAND_WLS_FINISHED_READ);
    return this->_levelReadings[this->_levelReadingNumber - 1];
  }
  return -1;
}

float WaterLevelSensor::readAvg()
{
  cLog("Reading the Water level sensor average", DebugLevel::DEBUG);
  this->read();
  
  return this->getAvg();;
}
float WaterLevelSensor::getAvg(){
  float avg = 0;
  for (int j = 0; j < WATER_LEVEL_READINGS_COUNT; ++j)
  {
    avg += this->_levelReadings[j];
  }

  return avg / WATER_LEVEL_READINGS_COUNT;
}
int WaterLevelSensor::nextState(int command)
{

  switch (this->state)
  {
  case WaterLevelSensorStates::STATE_WLS_IDLE:
    if (command == WaterLevelSensorCommand::COMMAND_WLS_READ)
    {
      this->state = WaterLevelSensorStates::STATE_WLS_READING;
    }
    break;
  case WaterLevelSensorStates::STATE_WLS_READING:

    if (command == WaterLevelSensorCommand::COMMAND_WLS_FINISHED_READ)
    {
      this->state = WaterLevelSensorStates::STATE_WLS_IDLE;
    }
    break;

  default:
    break;
  }
  return this->state;
}

bool WaterLevelSensor::init()
{
  if (this->_initFunc())
  {
    //set all values to full wet
    for (int j = 0; j < WATER_LEVEL_READINGS_COUNT; j++)
    {
      this->_levelReadings[j] = 100.0;
    }
    return true;
  }
  return false;
}
bool WaterLevelSensor::tick()
{
  return true;
}