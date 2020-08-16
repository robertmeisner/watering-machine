#include "Light.h"
#include "StateMachineInterfaces/SwitchStateMachine.h"
#include "../Utils/CustomLog.h"

Light::Light(bool onFunc(), bool offFunc(), bool initFunc() ) : SimpleSwitch(onFunc, offFunc, initFunc){};
bool Light::init()
{
    cLog("Initiating Light");
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
    this->sinceLastChangeChrono = millis();
    return true;
};
unsigned long Light::getDurationSinceLastChange()
{
    return millis() - this->sinceLastChangeChrono;
}