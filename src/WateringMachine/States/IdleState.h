#ifndef IDLE_STATE_H
#define IDLE_STATE_H
#include "WateringMachineStateBase.h"
class WateringMachine;
/**
 * During Idle state Watering Machine is monitoring moisture and time since last watering or lighting and switches to other states if needed.
 */
class IdleState : public WateringMachineStateBase
{
public:
    IdleState();
    IdleState(WateringMachine *wm);
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleIdle();
    bool init();
    bool tick();
    StateType type = StateType::IDLE_STATE;

protected:
};
#endif