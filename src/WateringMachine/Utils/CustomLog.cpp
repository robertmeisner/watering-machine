#include "CustomLog.h"

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

void cLogSetDebugLevel(DebugLevel v)
{
    currentDebugLevel = v;
}