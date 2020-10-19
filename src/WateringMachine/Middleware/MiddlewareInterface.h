#include "../States/StateTypeEnum.h"
#ifndef MIDDLEWARE_INTERFACE_H
#define MIDDLEWARE_INTERFACE_H
class WateringMachine;
class WateringMachineStateBase;
/**
 * Abstract class describing common interface of all State Machines.
 */
class MiddlewareInterface
{
public:
    MiddlewareInterface();
    // Class destructor for MiddlewareInterface
    ~MiddlewareInterface() {}
    /**
   * Initiates the state
   * @return {bool}  : 
   */
    virtual bool init(WateringMachine* wm);
    /**
   * Tick method simulates a passage of time.
   * Enables implementation timers or timeouts.
   * @return {bool}  : 
   */
    virtual bool tick(WateringMachine* wm);

    /**
     * 
     * @return {WateringMachineStateBase*}  : 
     */
    virtual bool stateChange(WateringMachine* wm,WateringMachineStateBase* oldState, WateringMachineStateBase* nextState);

protected:
};
#endif