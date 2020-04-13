#ifndef SWITCH_STATE_MACHINE_H
#include "StateMachine.h"
#define SWITCH_STATE_MACHINE_H
enum SwitchStates
{
  SWITCH_OFF,
  SWITCH_ON
};
enum SwitchCommand
{
  COMMAND_ON,
  COMMAND_OFF
};
class SwitchStateMachine : public StateMachine
{
public:
  SwitchStateMachine() {}
  int state = SwitchStates::SWITCH_OFF;
  /**
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