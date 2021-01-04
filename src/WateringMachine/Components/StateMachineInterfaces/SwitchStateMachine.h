#ifndef SWITCH_STATE_MACHINE_H
#include "StateMachine.h"
#define SWITCH_STATE_MACHINE_H
enum SwitchStates
{
  SWITCH_OFF = 0,
  SWITCH_ON = 1
};
enum SwitchCommand
{
  COMMAND_OFF = 0,
  COMMAND_ON = 1
};
class SwitchStateMachine : public StateMachine
{
public:
  SwitchStateMachine();
  /*
   * Turns on the device
   * @return {bool}  : true if succesful, false otherwise
   */
  virtual bool turnOn() = 0;
  /**
   * Turns off the device
   * @return {bool}  : true if succesful, false otherwise
   */
  virtual bool turnOff() = 0;
  virtual ~SwitchStateMachine() {} // Destructor
protected:
  int nextState(int command);
};
#endif