#ifndef ARDUINO_LOGGING_MIDDLEWARE_H
#define ARDUINO_LOGGING_MIDDLEWARE_H
#include "../MiddlewareInterface.h"
#include "../../Utils/DebugLevelEnum.h"
class WateringMachine;

/**
 * During Watering state pumps are turned on until defined moisture thresholds are met.
 */
class ArduinoLoggingMiddleware : public MiddlewareInterface
{
public:
    bool init();
    bool tick();
    bool stateChange(StateType nextState);
    static DebugLevel currentDebugLevel;

private:
    void log(String message, int logType);
    bool showDebugLevel(DebugLevel v);
};
#endif