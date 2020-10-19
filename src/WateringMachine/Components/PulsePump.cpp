#include "PulsePump.h"
#include "../Utils/CustomLog.h"
// IMPLEMENTATION
bool PulsePumpInitMockFunc()
{
    return true;
}
PulsePump::PulsePump(bool (*startFunc)(), bool (*stopFunc)(), bool (*initFunc)(), unsigned long (*timeFunc)(), unsigned long _pulseDuration, unsigned long _pulseInterval) : SimplePump(startFunc, stopFunc, initFunc), pulseDuration(_pulseDuration), pulseInterval(_pulseInterval)
{
    this->_timeFunc=timeFunc;
}
bool PulsePump::init()
{
    cLog("PulsePump::init");
    return SimplePump::init();
}
bool PulsePump::start()
{
    this->isPulsing = true;
    this->lastPulseChange = 0;
    return SimplePump::start();
}
bool PulsePump::tick()
{
    if (this->state == PumpStates::STATE_ON)
    {
        if (this->isPulsing && (this->_timeFunc() - this->lastPulseChange) > this->pulseDuration)
        {
            this->pulsePause();
        }
        else if (!this->isPulsing && (this->_timeFunc() - this->lastPulseChange) > this->pulseInterval)
        {
            this->pulse();
        }
    }
    return SimplePump::tick();
}
bool PulsePump::pulse()
{
    cLog("PulsePump is pulsing", DebugLevel::DEBUG);
    this->lastPulseChange = this->_timeFunc();
    this->isPulsing = true;
    return this->_startFunc();
}
bool PulsePump::pulsePause()
{
    cLog("PulsePump is pausing", DebugLevel::DEBUG);
    this->lastPulseChange = this->_timeFunc();
    this->isPulsing = false;
    return this->_stopFunc();
}