#ifndef WATERING_STATE_H
#define WATERING_STATE_H
#include "WateringMachineStateBase.h"

//#include "../WateringMachine.h"
class WateringMachine;
class WateringState : public WateringMachineStateBase
{
public:
    WateringState();
    WateringState(WateringMachine *wm);
    //using WateringMachineStateBase::WateringMachineStateBase;
    const char *getName();
    bool handleWatering();
    bool handleLighting();
    bool handleMoistureReading();
    bool handleIdle();
    bool init();
    bool tick();
    StateType type = StateType::WATERING_STATE;

protected:
    int sensorsAverage = 100;
};
#endif