#ifndef IDLE_STATE_H
#define IDLE_STATE_H
#include "WateringMachineStateBase.h"
class WateringMachine;
//#include "../WateringMachine.h"
class IdleState : public WateringMachineStateBase
{
public:
    IdleState();
    IdleState(WateringMachine *wm);
    //using WateringMachineStateBase::WateringMachineStateBase;
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleIdle();
    bool init();
    bool tick();
    StateType type = StateType::IDLE_STATE;

protected:
    //WateringMachine context;
};
#endif