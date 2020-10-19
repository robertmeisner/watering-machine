#ifndef ARDUINO_LOGGING_MIDDLEWARE_H
#define ARDUINO_LOGGING_MIDDLEWARE_H
#include <WateringMachine/Middleware/MiddlewareInterface.h>
#include  <string>
class WateringMachine;

/**
 * During Watering state pumps are turned on until defined moisture thresholds are met.
 */
class MiddlewareTest : public MiddlewareInterface
{
public:
    bool init();
    bool tick();
    bool stateChange(StateType nextState);

};
#endif