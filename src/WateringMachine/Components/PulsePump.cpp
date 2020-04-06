#include "PulsePump.h"
#include "../Utils/CustomLog.h"
// IMPLEMENTATION
bool PulsePumpInitMockFunc()
{
    return true;
}
PulsePump::PulsePump(bool (*startFunc)(), bool (*stopFunc)(), bool (*initFunc)()) : SimplePump(startFunc, stopFunc, initFunc)
{
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
        if (this->isPulsing && (millis() - this->lastPulseChange) > this->pulseDuration)
        {
            this->pulsePause();
        }
        else if (!this->isPulsing && (millis() - this->lastPulseChange) > this->pulseInterval)
        {
            this->pulse();
        }
    }
    return SimplePump::tick();
}
bool PulsePump::pulse()
{
    cLog("PulsePump is pulsing", DebugLevel::DEBUG);
    this->lastPulseChange = millis();
    this->isPulsing=true;
    return this->_startFunc();
}
bool PulsePump::pulsePause()
{
    cLog("PulsePump is pausing", DebugLevel::DEBUG);
    this->lastPulseChange = millis();
    this->isPulsing=false;
    return this->_stopFunc();
}