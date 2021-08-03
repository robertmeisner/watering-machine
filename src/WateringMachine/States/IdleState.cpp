#include <string>
#include <cstdlib>
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

bool IdleState::handleIdle()
{
    cLog("Idle can't be changed to Idle", DebugLevel::WARNING);
    return true;
}
bool IdleState::init()
{
    cLog("Initiating Idle State");
    return true;
}
bool IdleState::tick()
{
    // ~every 10th time (on avg :) ) 
    //TODO should be replaced with timer function
    if (rand() % 15 + 1==15)
    { 
        unsigned int sensorsAvg = this->context->getMoistureAvg();
        //if avg moisture is higher than XXX stop Watering

        std::string json = "JSON = ";
        //serializeJson(this->context->config, json);
        //cLog(json);

        if (sensorsAvg < this->context->config->MOISTURE_TRESHOLD && this->context->config->WATERING_MIN_INTERVAL < this->context->pump->getDurationSinceLastChange() && this->context->config->WATERING_MIN_INTERVAL < this->context->light->getDurationSinceLastChange())
        {
            cLog("Moisture under MOISTURE_TRESHOLD or WATERING_MIN_INTERVAL is lower than getDurationSinceLastChange of light/pump");
            return this->handleWatering();
        }

        else if (this->context->pump->getDurationSinceLastChange() > this->context->config->WATERING_MAX_INTERVAL)
        {
            cLog("Moisture duration since last change over WATERING_MAX_INTERVAL");
            return this->handleWatering();
        }
        else if (this->context->light->getDurationSinceLastChange() > this->context->config->LIGHTING_INTERVAL)
        {
            cLog("Time passed since last ligting is higher than LIGHTING_INTERVAL");
            return this->handleLighting();
        }
        else if (sensorsAvg > this->context->config->MOISTURE_TRESHOLD)
        {
            cLog("Moisture over MOISTURE_TRESHOLD");
        }
    }
    return true;
}