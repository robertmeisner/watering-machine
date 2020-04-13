#ifndef LIGHTING_STATE_H
#define LIGHTING_STATE_H
#include "WateringMachineStateBase.h"
class WateringMachine;
/**
 * During Lighting state Watering Machine turns the lights on to stimulate photosynthesis and to promote plant biomass growth.
 */
class LightingState : public WateringMachineStateBase
{
public:
    LightingState();
    LightingState(WateringMachine *wm);
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleIdle();
    bool init();
    bool tick();
    StateType type = StateType::LIGHTING_STATE;

protected:
};

#endif