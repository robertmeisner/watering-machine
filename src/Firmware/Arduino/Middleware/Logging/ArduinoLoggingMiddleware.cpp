#include <Arduino.h>
#include "ArduinoLoggingMiddleware.h"
DebugLevel ArduinoLoggingMiddleware::currentDebugLevel= DebugLevel::INFO;
bool ArduinoLoggingMiddleware::init(WateringMachine* wm){
    Serial.println("ArduinoLoggingMiddleware initiated.");
};

bool ArduinoLoggingMiddleware::tick(WateringMachine* wm){
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
bool ArduinoLoggingMiddleware::stateChange(WateringMachine* wm,WateringMachineStateBase* oldState, WateringMachineStateBase* nextState){

};
bool ArduinoLoggingMiddleware::showDebugLevel(DebugLevel v){
    if (v <= this->currentDebugLevel)
        return true;
    else
        return false;
};