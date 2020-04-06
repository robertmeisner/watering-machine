#include "SimpleSwitch.h"
#include "../Utils/CustomLog.h"
//IMPLEMENTATION
bool SimpleSwitchInitMockFunc()
{
  return true;
}
SimpleSwitch::SimpleSwitch(bool onFunc(), bool offFunc(), bool initFunc()) : SwitchStateMachine()
{
  this->_onFunc = onFunc;
  this->_offFunc = offFunc;
  if (initFunc != nullptr)
    this->_initFunc = initFunc;
  else
    this->_initFunc = SimpleSwitchInitMockFunc;
}
bool SimpleSwitch::init()
{
  cLog("Initiating SimpleSwitch");
  return this->_initFunc();
}
bool SimpleSwitch::turnOff()
{
  this->_offFunc();
  return SwitchStates::SWITCH_OFF == this->nextState(SwitchCommand::COMMAND_OFF);
}
bool SimpleSwitch::turnOn()
{

  this->_onFunc();
  return SwitchStates::SWITCH_ON == this->nextState(SwitchCommand::COMMAND_ON);
}