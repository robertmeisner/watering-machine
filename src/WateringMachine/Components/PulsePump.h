#ifndef PulsePump_h
#include "SimplePump.h"
#define PulsePump_h
/**
 * 
 */
class PulsePump : public SimplePump
{
public:
    /**
     * The PulsePump operates in a pulsating manner. 
     * After turning on, the engine starts for X seconds, then stops for Y seconds. 
     * Cycle repeats untill pump gets turned off.
     * 
     * @param  {bool(*)()} startFunc        : 
     * @param  {bool(*)()} stopFunc         : 
     * @param  {bool(*)()=nullptr} initFunc : 
     */
    PulsePump(bool (*startFunc)(), bool (*stopFunc)(), bool (*initFunc)() = nullptr);
    bool start();
    bool tick();
protected:
    /**
     * Turns the pump on fot the duration equal to pulseDuration
     * @return {bool}  : true if successful
     */
    bool pulse();
    /**
     * Turns the pump off fot the duration equal to pulseInterval
     * @return {bool}  : true if successful
     */
    bool pulsePause();
    bool isPulsing = false;
    unsigned lastPulseChange = 0;
    unsigned long pulseDuration = 1000 * 7;
    unsigned long pulseInterval = 1000 * 3;
};

#endif