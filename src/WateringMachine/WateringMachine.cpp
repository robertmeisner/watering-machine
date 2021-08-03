#include "WateringMachine.h"
#include "WateringMachineConfig.h"
#include "Components/Light.h"
#include "Components/MoistureSensor.h"
#include "Components/WaterLevelSensor.h"
#include "Components/SimplePump.h"
#include "States/WateringMachineStateBase.h"
#include "States/IdleState.h"
#include "States/StateFactory.h"
#include "Utils/CustomLog.h"
#include "Middleware/MiddlewareInterface.h"
#include <stdio.h>

WateringMachine::WateringMachine(WateringMachineConfig *doc, StateFactory *sf, Light *l, SimplePump *sp, std::vector<MoistureSensor *> *ms, WaterLevelSensor *wls, std::vector<MiddlewareInterface *> *mdlwrs) : state(nullptr), config(doc), lastStats((new WateringMachineStats())), stateFactory(sf), light(l), pump(sp), moistureSensors(ms),waterLevelSensor(wls), middlewares(mdlwrs)
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
    if (this->state != nullptr)
    {
        this->lastStats->statePrevious = this->state->getName();
    }
    WateringMachineStateBase *oldState = this->state;
    this->state = this->stateFactory->getState(type, this);
    this->state->init();
    for (std::vector<MiddlewareInterface *>::iterator it = this->middlewares->begin(); it != this->middlewares->end(); ++it)
    {
        (*it)->stateChange(oldState, this->state);
    }
    delete oldState;
    return this;
}
bool WateringMachine::setConfig(WateringMachineConfig *conf)
{
    //copies right object to the left object so we should have nono memory leak
    *this->config = *conf;
    //std::cout << conf->WATERING_STOP_TRESHOLD;
    //std::cout << this->config->WATERING_STOP_TRESHOLD;
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
    this->waterLevelSensor->init();
    //set initital state
    this->setState(StateType::IDLE_STATE); //state's init is called here
    return true;
}
bool WateringMachine::tick()
{
    for (std::vector<MiddlewareInterface *>::iterator it = this->middlewares->begin(); it != this->middlewares->end(); ++it)
    {
        (*it)->tick();
    }
    this->light->tick();
    for (std::vector<MoistureSensor *>::iterator it = this->moistureSensors->begin(); it != this->moistureSensors->end(); ++it)
    {
        (*it)->tick();
    }
    this->pump->tick();
    this->waterLevelSensor->tick();
    this->state->tick();
    return true;
}
WateringMachineStats *WateringMachine::getStats()
{
    this->lastStats->pumpOn = this->pump->state == PumpStates::STATE_ON;
    this->lastStats->pumpDurationSinceLastChange = this->pump->getDurationSinceLastChange();
    this->lastStats->lightOn = this->light->isOn();
    this->lastStats->lightDurationSinceLastChange = this->light->getDurationSinceLastChange();
    this->lastStats->state = this->state->getName();
    this->lastStats->averageMoisture = this->getMoistureAvg();
    this->lastStats->waterLevel=this->waterLevelSensor->readAvg();

    int jj = 0;
    for (std::vector<MoistureSensor *>::iterator it = this->moistureSensors->begin(); it != this->moistureSensors->end(); ++it)
    {
        this->lastStats->moistureSensorActive[jj] = true;
        this->lastStats->moistureSensorReadings[jj] = (*it)->getAvg();
        //std::cout << "average 1 sens---------";
        //std::cout << this->lastStats->moistureSensorReadings[jj];
        //std::cout << "\n";
        jj++;
    }
    //std::cout << "sensors---------";
    //std::cout << jj;
    //std::cout << "\n";
    return this->lastStats;
}
/**
     * Logic of each command.
     * @param  {char*} commandLine : 
     * @return {bool}              : 
     */
