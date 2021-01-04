#ifndef ARDUINO_LOGGING_MIDDLEWARE_H
#define ARDUINO_LOGGING_MIDDLEWARE_H
#include "../../../../WateringMachine/Middleware/MiddlewareInterface.h"
#include "../../../../WateringMachine/Utils/DebugLevelEnum.h"
class WateringMachine;

/**
 * During Watering state pumps are turned on until defined moisture thresholds are met.
 */
class ArduinoLoggingMiddleware : public MiddlewareInterface
{
public:
    bool init(WateringMachine* wm);
    bool tick();
    bool stateChange(WateringMachineStateBase* oldState, WateringMachineStateBase* nextState);
    static DebugLevel currentDebugLevel;

private:
    void log(String message, int logType);
    bool showDebugLevel(DebugLevel v);
};
#endif