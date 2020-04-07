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
    if (this->context->pump.stop())
    {
        if (this->context->light.turnOn())
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
}

bool WateringState::handleIdle()
{
    cLog("Changing WateringState to IdleState..");
    if (this->context->pump.stop())
    {
        cLog("Changing state from WateringState to IdleState");
        this->context->setState(StateType::IDLE_STATE);
        return true;
    }
}
bool WateringState::init()
{
    cLog("Initiating the WateringState");
    if (!this->context->pump.start())
    {
        cLog("Couldn't start the pump, switching back to Idle state.");
        return this->handleIdle();
    }
    cLog("Initiating of the WateringState has finished");
    return true;
}
bool WateringState::tick()
{
    cLog("Watering State tick started", DebugLevel::DEBUG);
    // if last time checked is 2 min ago or more
    // read moisture

    float sensorsAvg = this->context->getMoistureAvg();
    //if avg moisture is higher than WATERING_STOP_TRESHOLD stop Watering and go Idle
    if (sensorsAvg > (this->context->config.WATERING_STOP_TRESHOLD))
    {
        cLog(String("Moisture is over WATERING_STOP_TRESHOLD: ") + String(sensorsAvg) + ">" + String(this->context->config.WATERING_STOP_TRESHOLD), DebugLevel::DEBUG);
        //cLog( (this->context->config['MOISTURE_TRESHOLD']);
        cLog("Stopping Watering");
        return this->handleIdle();
    }
    else if (this->context->pump.getDurationSinceLastChange() > this->context->config.WATERING_MAX_DURATION)
    {
        cLog(String("Watering takes too long. Watering duration is over WATERING_MAX_DURATION:") + String(this->context->pump.getDurationSinceLastChange()) + ">" + this->context->config.WATERING_MAX_DURATION, DebugLevel::DEBUG);
        cLog("Stopping Watering");
        return this->handleIdle();
    }
    String str=String("Moisture sensor is below WATERING_STOP_TRESHOLD: ")  + sensorsAvg + String("<") + this->context->config.WATERING_STOP_TRESHOLD;
    str+=" "+String("Watering duration is below WATERING_MAX_DURATION ") + this->context->pump.getDurationSinceLastChange() + String("<") + sensorsAvg + String("<") + this->context->config.WATERING_MAX_DURATION;
    cLog(str, DebugLevel::DEBUG);
    return true;
}
