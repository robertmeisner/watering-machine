#include "StateFactory.h"
#include "LightingState.h"
#include "WateringState.h"
#include "IdleState.h"
StateFactory::StateFactory() {}
WateringMachineStateBase *StateFactory::getState(StateType type, WateringMachine *m)
{

    switch (type)
    {
    case StateType::WATERING_STATE:
    {
        WateringMachineStateBase *a = new WateringState(m);
        return a;
        break;
    }
    case StateType::LIGHTING_STATE:
    {
        WateringMachineStateBase *b = new LightingState(m);
        return b;
        break;
    }

    case StateType::IDLE_STATE:
    {
        WateringMachineStateBase *c = new IdleState(m);
        return c;
        break;
    }

    default:
    {
        WateringMachineStateBase *c = new IdleState(m);
        return c;
        break;
    }
    }
}