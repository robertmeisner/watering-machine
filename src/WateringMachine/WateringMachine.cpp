#include "WateringMachine.h"
#include "WateringMachineConfig.h"
#include "Components/Light.h"
#include "Components/MoistureSensor.h"
#include "Components/SimplePump.h"
#include "States/WateringMachineStateBase.h"
#include "States/IdleState.h"
#include "States/StateFactory.h"
#include "Utils/CustomLog.h"
#include "Middleware/MiddlewareInterface.h"
#include <stdio.h>

WateringMachine::WateringMachine(WateringMachineConfig *doc, StateFactory *sf, Light *l, SimplePump *sp, std::vector<MoistureSensor *> *ms, std::vector<MiddlewareInterface *> *mdlwrs) : state(nullptr), config(doc), lastStats((new WateringMachineStats())), stateFactory(sf), light(l), pump(sp), moistureSensors(ms), middlewares(mdlwrs)
{
}
bool WateringMachine::turnLight()
{
    return this->state->handleLighting();
}
bool WateringMachine::turnIdle()
{
    return this->state->handleIdle();
}
bool WateringMachine::turnWatering()
{
    return this->state->handleWatering();
}
WateringMachine *WateringMachine::setState(StateType type)
{
    WateringMachineStateBase *oldState = this->state;
    this->state = this->stateFactory->getState(type, this);
    this->state->init();
    for (std::vector<MiddlewareInterface *>::iterator it = this->middlewares->begin(); it != this->middlewares->end(); ++it)
    {
        (*it)->stateChange(this, oldState, this->state);
    }
    delete (oldState);
    return this;
}
bool WateringMachine::setConfig(WateringMachineConfig *conf)
{
    WateringMachineConfig *oldConfig = this->config;
    this->config = conf;
    delete (oldConfig);
    return true;
}
float WateringMachine::getMoistureAvg()
{
    if (this->moistureSensors->size() == 0)
    {
        cLog("No Moisture Sensors detected.", DebugLevel::FATAL);
        return 100;
    }

    float avg = 0.0;
    for (std::vector<MoistureSensor *>::iterator it = this->moistureSensors->begin(); it != this->moistureSensors->end(); ++it)
    {
        avg += (*it)->readAvg();
    }
    std::string str = "Average for all Moisture sensors reads: ";
    char array[10];
    snprintf(array, sizeof(array), "%f", (avg / this->moistureSensors->size()));
    str += array;
    cLog(str);
    return avg / this->moistureSensors->size();
}
bool WateringMachine::init()
{
    for (std::vector<MiddlewareInterface *>::iterator it = this->middlewares->begin(); it != this->middlewares->end(); ++it)
    {
        (*it)->init(this);
    }
    // inititate the components
    this->light->init();
    for (std::vector<MoistureSensor *>::iterator it = this->moistureSensors->begin(); it != this->moistureSensors->end(); ++it)
    {

        (*it)->init();
    }
    this->pump->init();
    //set initital state
    this->setState(StateType::IDLE_STATE); //state's init is called here
    return true;
}
bool WateringMachine::tick()
{
    for (std::vector<MiddlewareInterface *>::iterator it = this->middlewares->begin(); it != this->middlewares->end(); ++it)
    {
        (*it)->tick(this);
    }
    this->light->tick();
    for (std::vector<MoistureSensor *>::iterator it = this->moistureSensors->begin(); it != this->moistureSensors->end(); ++it)
    {
        (*it)->tick();
    }
    this->pump->tick();
    this->state->tick();
    return true;
}
WateringMachineStats *WateringMachine::getCurrentStats()
{
    this->lastStats->wateringOn = this->pump->state == PumpStates::STATE_ON;
    this->lastStats->lightOn = this->light->isOn();
    this->lastStats->stateName = this->state->getName();
    int jj = 0;
    for (std::vector<MoistureSensor *>::iterator it = this->moistureSensors->begin(); it != this->moistureSensors->end(); ++it)
    {
        this->lastStats->moistureSensorActive[jj] = true;
        this->lastStats->moistureSensorReadings[jj] = (*it)->getAvg();
        jj++;
    }
    return this->lastStats;
}
/**
     * Logic of each command.
     * @param  {char*} commandLine : 
     * @return {bool}              : 
     */
