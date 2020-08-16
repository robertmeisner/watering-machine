#include "../States/StateTypeEnum.h"
#ifndef MIDDLEWARE_INTERFACE_H
#define MIDDLEWARE_INTERFACE_H
class WateringMachine;
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
    virtual bool init();
    /**
   * Tick method simulates a passage of time.
   * Enables implementation timers or timeouts.
   * @return {bool}  : 
   */
    inline virtual bool tick();

    /**
     * 
     * @return {WateringMachineStateBase*}  : 
     */
    virtual bool stateChange(StateType nextState);
    bool setContext(WateringMachine *cont);

protected:
    WateringMachine *context;
};
#endif