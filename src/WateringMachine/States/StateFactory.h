#ifndef STATE_FACTORY_H
#define STATE_FACTORY_H
#include "StateTypeEnum.h"
class WateringMachineStateBase;
class WateringMachine;
class StateFactory
{
public:
    StateFactory();
    // WateringMachineStateBase* getState(StateType type);
    WateringMachineStateBase* getState(StateType type,WateringMachine *m);
};

#endif
