
//https://www.drdobbs.com/cpp/state-patterns-c/184404132?pgno=1
#ifndef WateringMachine_h
#define WateringMachine_h
#include <vector>

#include "States/StateTypeEnum.h"
#include "WateringMachineConfig.h"

class WateringMachineStateBase;
class Light;
struct WateringMachineConfig;
class MoistureSensor;
class SimplePump;
class StateFactory;

class WateringMachine
{
public:
    /**
     * WateringMachine 
     * saadsadasd
     * asdasdasdasdsa
     * sad
     * @param  {WateringMachineConfig} doc                   : 
     * @param  {StateFactory} sf                             : 
     * @param  {Light} l                                     : 
     * @param  {SimplePump} sp                               : 
     * @param  {std::vector<MoistureSensor>} moistureSensors : 
     */
    WateringMachine(WateringMachineConfig &doc, StateFactory &sf, Light &l, SimplePump &sp, std::vector<MoistureSensor> &moistureSensors);
    void turnLight();
    void turnIdle();
    void turnWatering();
    bool init();
    void tick();
    float getMoistureAvg();
    WateringMachine *setState(StateType type);
    WateringMachineStateBase *state;
    WateringMachineConfig &config;
    Light &light;
    std::vector<MoistureSensor> &moistureSensors;
    SimplePump &pump;
    StateFactory &stateFactory;
};
#endif
