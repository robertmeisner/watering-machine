#ifndef CustomDebug_h
#include <Arduino.h>
#define CustomDebug_h
enum DebugLevel
{
    INFO,
    VERBOSE,
    WARNING,
    ERROR,
    DEBUG,
    FATAL,
    ALL,
    OFF
};
inline const char *DebugLevelToString(DebugLevel v);
void cLog(const char *message, DebugLevel v=DebugLevel::INFO);
void cLog(const String message, DebugLevel v=DebugLevel::INFO);
void cLog(const std::string& message, DebugLevel v=DebugLevel::INFO);
#endif