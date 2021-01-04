#include <Arduino.h>
#include "ArduinoLoggingMiddleware.h"
DebugLevel ArduinoLoggingMiddleware::currentDebugLevel = DebugLevel::INFO;
bool ArduinoLoggingMiddleware::init(WateringMachine *wm)
{
    Serial.println("ArduinoLoggingMiddleware initiated.");
    return true;
};

bool ArduinoLoggingMiddleware::tick()
{
    return true;
};

void ArduinoLoggingMiddleware::log(String message, int logType)
{
    String mystring(message);
    if (!this->showDebugLevel(static_cast<DebugLevel>(logType)))
        return;
    String str = "";
    str += DebugLevelToString(static_cast<DebugLevel>(logType));
    str += " - ";
    str += mystring;
    Serial.println(str);
};
bool ArduinoLoggingMiddleware::stateChange(WateringMachineStateBase *oldState, WateringMachineStateBase *nextState)
{
    return true;
};
bool ArduinoLoggingMiddleware::showDebugLevel(DebugLevel v)
{
    if (v <= this->currentDebugLevel)
        return true;
    else
        return false;
};