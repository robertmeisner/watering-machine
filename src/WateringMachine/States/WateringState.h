#ifndef WATERING_STATE_H
#define WATERING_STATE_H
#include "WateringMachineStateBase.h"
class WateringMachine;
/**
 * During Watering state pumps are turned on until defined moisture thresholds are met.
 */
class WateringState : public WateringMachineStateBase
{
public:
    WateringState();
    WateringState(WateringMachine *wm);
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleMoistureReading();
    bool handleIdle();
    bool init();
    bool tick();
    StateType type = StateType::WATERING_STATE;

protected:
};
#endif