#include "Light.h"
#include "StateMachineInterfaces/SwitchStateMachine.h"
#include "../Utils/CustomLog.h"

Light::Light(bool onFunc(), bool offFunc(), bool initFunc(), unsigned long (*timeFunc)() ) : SimpleSwitch(onFunc, offFunc, initFunc)
{
    this->_timeFunc = timeFunc;
};
bool Light::init()
{
    cLog("Initiating Light");
    this->restartTimer();
    return SimpleSwitch::init();
}
bool Light::turnOn()
{
    cLog("Turning on the Light");
    if (SimpleSwitch::turnOn())
    {
        return this->restartTimer();
    }
    return false;
};
bool Light::turnOff()
{
    cLog("Turning off the Light");
    if (SimpleSwitch::turnOff())
    {
        return this->restartTimer();
    }
    return false;
};
bool Light::isOn()
{
    return this->state == SwitchStates::SWITCH_ON;
}
bool Light::restartTimer()
{
    cLog("Restarting the Light timer");
    this->sinceLastChangeChrono = this->_timeFunc();
    return true;
};
unsigned long Light::getDurationSinceLastChange()
{
    return this->_timeFunc() - this->sinceLastChangeChrono;
}