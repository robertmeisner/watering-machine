#include "SimplePump.h"
#include "../Utils/CustomLog.h"
// IMPLEMENTATION
bool SimplePumpInitMockFunc()
{
    return true;
}
SimplePump::SimplePump(bool (*startFunc)(), bool (*stopFunc)(), bool (*initFunc)(),unsigned long (*timeFunc)()) : PumpStateMachine()
{
    this->_startFunc = startFunc;
    this->_stopFunc = stopFunc;
    if (initFunc == nullptr)
    {
        this->_initFunc = SimplePumpInitMockFunc;
    }
    else
    {
        this->_initFunc = initFunc;
    }
    this->_timeFunc=timeFunc;
}
bool SimplePump::start()
{
    cLog("Starting the pump", DebugLevel::INFO);

    this->_startFunc();
    this->nextState(PumpCommand::COMMAND_START);
    this->sinceLastChangeChrono = this->_timeFunc();

    return this->state == PumpStates::STATE_ON;
}

bool SimplePump::stop()
{

    if (this->_stopFunc())
    {
        this->sinceLastChangeChrono = this->_timeFunc ();
        if (this->nextState(PumpCommand::COMMAND_STOP) == PumpStates::STATE_OFF)
            return true;
    }
    cLog("Couldn't stop the pump", DebugLevel::ERROR);
    return false;
}
unsigned long SimplePump::getDurationSinceLastChange()
{
    return this->_timeFunc() - this->sinceLastChangeChrono;
}

bool SimplePump::init()
{
    cLog("Initiating SimplePump", DebugLevel::DEBUG);
    return this->_initFunc();
}
bool SimplePump::tick()
{
  return true;
}