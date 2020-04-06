#ifndef LIGHTING_STATE_H
#define LIGHTING_STATE_H
#include "WateringMachineStateBase.h"
class WateringMachine;
class LightingState : public WateringMachineStateBase
{
public:
    LightingState();
    LightingState(WateringMachine *wm);
    //using WateringMachineStateBase::WateringMachineStateBase;
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleIdle();
    bool init();
    bool tick();
    StateType type = StateType::LIGHTING_STATE;
    //LightingState(WateringMachine* wm);

protected:
};

#endif