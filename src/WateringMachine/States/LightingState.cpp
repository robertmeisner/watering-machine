#include "LightingState.h"
#include "StateFactory.h"
#include "../WateringMachine.h"
#include "../Components/Light.h"
#include "../Components/SimplePump.h"
#include "../Utils/CustomLog.h"
//LightingState::LightingState(WateringMachine* wm): WateringMachineStateBase(wm){}
LightingState::LightingState() : WateringMachineStateBase{} {}
LightingState::LightingState(WateringMachine *wm) : WateringMachineStateBase{wm} {}
const char *LightingState::getName()
{
    return "LightingState";
}
bool LightingState::handleWatering()
{
    this->context->light.turnOff();

    if (!this->context->light.isOn())
    {
        if (this->context->pump.start())
        {
            cLog("Changing state from LightingState to WateringState");
            this->context->setState(StateType::WATERING_STATE);
            return true;
        }
    }
    return false;
}
bool LightingState::handleLighting()
{
    cLog("Lighting can't be handled when lighting", DebugLevel::WARNING);
    return false;
}
bool LightingState::handleIdle()
{
    cLog("LightingState::handleIdle", DebugLevel::DEBUG);
    this->context->light.turnOff();
    if (!this->context->light.isOn())
    {
        cLog("Changing state from LightingState to IdleState");
        this->context->setState(StateType::IDLE_STATE);
        return true;
    }
    else
    {
        cLog("Couldn't turn lights off", DebugLevel::ERROR);
    }
    return false;
};
bool LightingState::init()
{
    cLog("Initiating the LightingState");
    return this->context->light.turnOn();
};
bool LightingState::tick()
{
    int sensorsAvg = this->context->getMoistureAvg();
    if (this->context->light.getDurationSinceLastChange() > this->context->config.LIGHTING_DURATION)
    {
        cLog("Ligting duration exceeded the LIGHTING_DURATION: " + String(this->context->light.getDurationSinceLastChange()) + '>' + String(this->context->config.LIGHTING_DURATION));
        return this->handleIdle();
    }
    return true;
};
