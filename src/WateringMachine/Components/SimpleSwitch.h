
#ifndef SimpleSwitch_h
#include "StateMachineInterfaces/SwitchStateMachine.h"
#define SimpleSwitch_h
/**
 * 
 */
class SimpleSwitch : public SwitchStateMachine
{
public:
  /**
   * SimpleSwitch 
   * 
   * @param  {bool} onFunc()   : 
   * @param  {bool} offFunc()  : 
   * @param  {bool} initFunc() : 
   */
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