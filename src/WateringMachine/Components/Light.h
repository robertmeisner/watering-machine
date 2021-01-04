#ifndef Light_h
#include "SimpleSwitch.h"
#define Light_h 
/**
 * Controls Lighting devices
 * Derives SimpleSwitch class and extends it with ability to track how much time elapsed since last state chenge.
 */
class Light : public SimpleSwitch
{
public:
    /**
     * Light device constructor.
     * 
     * @param  {bool} onFunc()           : function used to turn the Light on
     * @param  {bool} offFunc()          : function used to turn the Light off
     * @param  {bool} initFunc()=nullptr : function used to init turn the Light
     */
    Light(bool onFunc(),bool offFunc(),bool initFunc()=nullptr, unsigned long (*timeFunc)() = nullptr);
    bool init();
    bool turnOn();
    bool turnOff();
    /**
     * Checks whether light is turned on
     * @return {bool}  : true if is Light is turned on
     */
    bool isOn();
    
    /**
     * Returns time elapsed since last state change - in millis.
     * Every state change 
     * @return {unsigned long}  : time elapsed since last state change - in millis
     */
    unsigned long getDurationSinceLastChange();

private:
    unsigned long (*_timeFunc)();
    unsigned long sinceLastChangeChrono=0;
    /**
     * Sets sinceLastChangeChrono to current timestamp. 
     * @return {bool}  : true if successful
     */
    bool restartTimer();
};

#endif
