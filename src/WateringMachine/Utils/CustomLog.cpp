#include "CustomLog.h"
inline const char *DebugLevelToString(DebugLevel v)
{
    switch (v)
    {
    case DebugLevel::INFO:
        return "INFO";
    case DebugLevel::VERBOSE:
        return "VERBOSE";
    case DebugLevel::WARNING:
        return "WARNING";
    case DebugLevel::ERROR:
        return "ERROR";
    case DebugLevel::DEBUG:
        return "DEBUG";
    case DebugLevel::FATAL:
        return "FATAL";
    default:
        return "[Unknown DebugLevel]";
    }
}
bool cLogShowDebugLevel(DebugLevel v)
{
    if (v <= currentDebugLevel)
        return true;
    else
        return false;
}
void cLog(const char *message, DebugLevel v /*=DebugLevel::INFO*/)
{
    if (!cLogShowDebugLevel)
        return;
    String str = "";
    str += DebugLevelToString(v);
    str += " - ";
    str += message;
    Serial.println(str);
}
void cLog(const String message, DebugLevel v /*=DebugLevel::INFO*/)
{
    if (!cLogShowDebugLevel)
        return;
    String str = "";
    str += DebugLevelToString(v);
    str += " - ";
    str += message;
    Serial.println(str);
}
void cLog(const std::string &message, DebugLevel v /*=DebugLevel::INFO*/)
{
    if (!cLogShowDebugLevel)
        return;
    String str = "";
    str += DebugLevelToString(v);
    str += " - ";
    str = message.c_str();
    Serial.println(str);
}

void cLogsetDebugLevel(DebugLevel v)
{
    currentDebugLevel = v;
}