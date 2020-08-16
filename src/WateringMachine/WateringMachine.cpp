#include "WateringMachine.h"
#include "WateringMachineConfig.h"
#include "Components/Light.h"
#include "Components/MoistureSensor.h"
#include "Components/SimplePump.h"
#include "States/WateringMachineStateBase.h"
#include "States/IdleState.h"
#include "States/StateFactory.h"
#include "Utils/CustomLog.h"
#include "Midleware/MiddlewareInterface.h"

WateringMachine::WateringMachine(WateringMachineConfig &doc, StateFactory &sf, Light &l, SimplePump &sp, std::vector<MoistureSensor> &ms, std::vector<MiddlewareInterface> &mdlwrs) : config(doc), stateFactory(sf), light(l), pump(sp), moistureSensors(ms), middlewares(mdlwrs)
{
}
bool WateringMachine::turnLight()
{
    this->state->handleLighting();
}
bool WateringMachine::turnIdle()
{
    this->state->handleIdle();
}
bool WateringMachine::turnWatering()
{
    this->state->handleWatering();
}
WateringMachine *WateringMachine::setState(StateType type)
{
    this->state = this->stateFactory.getState(type, this);
    this->state->init();
    return this;
}

float WateringMachine::getMoistureAvg()
{
    if (this->moistureSensors.size() == 0)
    {
        cLog("No Moisture Sensors detected.", DebugLevel::FATAL);
        return 100;
    }

    float avg = 0;
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        avg += it->readAvg();
    }

    cLog(String("Average for all Moisture sensors reads: ") + (avg / this->moistureSensors.size()));
    return avg / this->moistureSensors.size();
}
bool WateringMachine::init()
{
    for (std::vector<MiddlewareInterface>::iterator it = this->middlewares.begin(); it != this->middlewares.end(); ++it)
    {
        it->init();
    }
    // inititate the components
    this->light.init();
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        it->init();
    }
    this->pump.init();
    //set initital state
    this->setState(StateType::IDLE_STATE); //state's init is called here
}
bool WateringMachine::tick()
{
    for (std::vector<MiddlewareInterface>::iterator it = this->middlewares.begin(); it != this->middlewares.end(); ++it)
    {
        it->tick();
    }
    this->light.tick();
    for (std::vector<MoistureSensor>::iterator it = this->moistureSensors.begin(); it != this->moistureSensors.end(); ++it)
    {
        it->tick();
    }
    this->pump.tick();
    this->state->tick();
}
