#ifndef STATE_FACTORY_H
#define STATE_FACTORY_H
#include "StateTypeEnum.h"
class WateringMachineStateBase;
class WateringMachine;
/**
 * In StateFactory, we create object without exposing the creation logic to the client and refer to newly created object using a common interface.
 */
class StateFactory
{
public:
    /**
     * StateFactory constructor
     */
    StateFactory();
    // WateringMachineStateBase* getState(StateType type); //TODO add getState(StateType type)?
    /**
     * Generates WateringMachineStateBase object of concrete class based on given information.
     * 
     * @param  {StateType} type             : 
     * @param  {WateringMachine*} m         : 
     * @return {WateringMachineStateBase*}  : 
     */
    WateringMachineStateBase* getState(StateType type,WateringMachine *m);
};

#endif
