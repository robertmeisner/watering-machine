#include "IdleState.h"
#include "StateFactory.h"
#include "../WateringMachine.h"
#include "../WateringMachineConfig.h"
#include "../Components/Light.h"
#include "../Components/SimplePump.h"
#include "../Components/MoistureSensor.h"
#include "../Utils/CustomLog.h"
IdleState::IdleState() : WateringMachineStateBase{} {}
IdleState::IdleState(WateringMachine *wm) : WateringMachineStateBase{wm} {}
const char *IdleState::getName()
{
    return "IdleState";
}
bool IdleState::handleWatering()
{
    cLog("Changing state from IdleState to WateringState");
    return this->context->setState(StateType::WATERING_STATE)->state->type == StateType::WATERING_STATE;
}
bool IdleState::handleLighting()
{
    cLog("Changing state from IdleState to LightingState");
    return this->context->setState(StateType::LIGHTING_STATE)->state->type == StateType::LIGHTING_STATE;
}

bool IdleState::handleIdle() { cLog("Idle can't be changed to Idle", DebugLevel::WARNING); }
bool IdleState::init()
{
    cLog("Initiating Idle State");
}
bool IdleState::tick()
{
    int sensorsAvg = this->context->getMoistureAvg();
    //if avg moisture is higher than XXX stop Watering

    String json = "JSON = ";
    //serializeJson(this->context->config, json);
    //cLog(json);

    if (sensorsAvg < this->context->config.MOISTURE_TRESHOLD && this->context->config.WATERING_MIN_INTERVAL < this->context->pump.getDurationSinceLastChange())
    {
        cLog("Moisture under MOISTURE_TRESHOLD: " + String(sensorsAvg) + '<' + String(this->context->config.MOISTURE_TRESHOLD));
        return this->handleWatering();
    }

    else if (this->context->pump.getDurationSinceLastChange() > this->context->config.WATERING_MAX_INTERVAL)
    {
        cLog("Moisture duration since last change: " + String(this->context->pump.getDurationSinceLastChange()) + '>' + String(this->context->config.WATERING_MAX_INTERVAL));
        return this->handleWatering();
    }
    else if (this->context->light.getDurationSinceLastChange() > this->context->config.LIGHTING_INTERVAL)
    {
        cLog(String("Time passed since last ligting is higher than LIGHTING_INTERVAL: ") + String(this->context->light.getDurationSinceLastChange()) + String('>') + String(this->context->config.LIGHTING_INTERVAL));
        return this->handleLighting();
    }
    else if (sensorsAvg > this->context->config.MOISTURE_TRESHOLD)
    {
        cLog("Moisture over MOISTURE_TRESHOLD: " + String(sensorsAvg) + '>' + String(this->context->config.MOISTURE_TRESHOLD));
    }
}