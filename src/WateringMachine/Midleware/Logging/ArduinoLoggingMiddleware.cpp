#include <Arduino.h>
#include "ArduinoLoggingMiddleware.h"
DebugLevel ArduinoLoggingMiddleware::currentDebugLevel= DebugLevel::INFO;
bool ArduinoLoggingMiddleware::init(){

};

bool ArduinoLoggingMiddleware::tick(){};

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
bool ArduinoLoggingMiddleware::stateChange(StateType nextState){

};
bool ArduinoLoggingMiddleware::showDebugLevel(DebugLevel v){
    if (v <= this->currentDebugLevel)
        return true;
    else
        return false;
};