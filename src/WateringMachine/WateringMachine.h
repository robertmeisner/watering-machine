
//https://www.drdobbs.com/cpp/state-patterns-c/184404132?pgno=1
#ifndef WateringMachine_h
#define WateringMachine_h
#include <vector>

#include "States/StateTypeEnum.h"
#include "WateringMachineConfig.h"
#include "WateringMachineStats.h"

#include "./Utils/DebugLevelEnum.h"
#include "./Middleware/MiddlewareInterface.h"
class WateringMachineStateBase;
class Light;
struct WateringMachineConfig;
class MoistureSensor;
class SimplePump;
class StateFactory;

/**
 * Watering Machine main  class. 
 * 
 * Follows the State Design pattern.
 * Watering Machine can be in one of 3 states:
 * @see IdleState class
 * @see WateringState class
 * @see LightingState class
 * Check state classes implementation to see the state's logic.
 * 
 * Watering Machine contains components which are used to interface with hardware (e.g. pumps, lights, sensors).
 */
class WateringMachine
{
public:
    /**
     * WateringMachine constructor
     * @param  {WateringMachineConfig} doc                   : Config
     * @param  {StateFactory} sf                             : State factory class
     * @param  {Light} l                                     : Light component
     * @param  {SimplePump} sp                               : Pump component
     * @param  {std::vector<MoistureSensor>} moistureSensors : Vector of moisture sensor components
     */
    WateringMachine(WateringMachineConfig *doc, StateFactory *sf, Light *l, SimplePump *sp, std::vector<MoistureSensor *> *moistureSensors, std::vector<MiddlewareInterface *> *middlewares);

    /**
     * Attempts to change current state to Lighting.
     * @return {bool}  : 
     */
    bool turnLight();
    /**
     * Attempts to change current state to Idle.
     * @return {bool}  : 
     */
    bool turnIdle();
    /**
     * Attempts to change current state to Watering.
     * @return {bool}  : 
     */
    bool turnWatering();
    /**
     * Initiates current state and all components.
     * @return {bool}  : 
     */
    bool init();
    /**
    * Runs tick methods of state and all components.
    */
    bool tick();

    /**
     * Returns mean value of moisture level from all sensors
     * @return {float}  : moisture level. value from 0 to 100;
     */
    float getMoistureAvg();
    WateringMachineStats *getStats();
    WateringMachine *setState(StateType type);
    WateringMachineStateBase *state;
    bool setConfig(WateringMachineConfig *conf);
    WateringMachineConfig *config;
    WateringMachineStats *lastStats;
    StateFactory *stateFactory;
    Light *light;
    SimplePump *pump;

    std::vector<MoistureSensor *> *moistureSensors;
    std::vector<MiddlewareInterface *> *middlewares;

private:
};
#endif
