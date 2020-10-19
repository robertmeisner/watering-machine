#include "WateringState.h"
#include "../WateringMachine.h"
#include "../Components/SimplePump.h"
#include "../Components/Light.h"
#include "../Utils/CustomLog.h"
WateringState::WateringState() : WateringMachineStateBase{} {}
WateringState::WateringState(WateringMachine *wm) : WateringMachineStateBase{wm} {}
const char *WateringState::getName()
{
    const char *msg = "WateringState";
    return msg;
}
bool WateringState::handleLighting()
{
    if (this->context->pump->stop())
    {
        if (this->context->light->turnOn())
        {
            cLog("Changing state from WateringState to LightingState");
            this->context->setState(StateType::LIGHTING_STATE);
            return true;
        }
    }
    return false;
};
bool WateringState::handleWatering()
{
    //do nothing?
    cLog("Watering can't be handled when watering", DebugLevel::WARNING);
    return false;
}

bool WateringState::handleIdle()
{
    if (this->context->pump->stop())
    {
        cLog("Changing state from WateringState to IdleState", DebugLevel::DEBUG);
        this->context->setState(StateType::IDLE_STATE);
        return true;
    }
    return false;
}
bool WateringState::init()
{
    cLog("Initiating the WateringState");
    if (!this->context->pump->start())
    {
        cLog("Couldn't start the pump, switching back to Idle state.", DebugLevel::WARNING);
        return this->handleIdle();
    }
    return true;
}
bool WateringState::tick()
{
    cLog("Watering State tick started", DebugLevel::DEBUG);
    // if last time checked is 2 min ago or more
    // read moisture

    float sensorsAvg = this->context->getMoistureAvg();
    //if avg moisture is higher than WATERING_STOP_TRESHOLD stop Watering and go Idle
    if (sensorsAvg > (this->context->config->WATERING_STOP_TRESHOLD))
    {
        cLog(("Moisture is over WATERING_STOP_TRESHOLD: "), DebugLevel::DEBUG);
        //cLog( (this->context->config['MOISTURE_TRESHOLD']);
        cLog("Stopping Watering");
        return this->handleIdle();
    }
    else if (this->context->pump->getDurationSinceLastChange() > this->context->config->WATERING_MAX_DURATION)
    {
        cLog("Watering takes too long. Watering duration is over WATERING_MAX_DURATION", DebugLevel::DEBUG);
        cLog("Stopping Watering");
        return this->handleIdle();
    }
    cLog("Moisture sensor is below WATERING_STOP_TRESHOLD and WATERING_MAX_DURATION. continuing...", DebugLevel::DEBUG);
    return true;
}
