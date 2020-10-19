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
    if (!cLogShowDebugLevel(v))
        return;
    std::string str = "";
    str += DebugLevelToString(v);
    str += " - ";
    str += message;
    str += "\n";
    std::cout << str;
}

void cLog(const std::string &message, DebugLevel v /*=DebugLevel::INFO*/)
{
    if (!cLogShowDebugLevel(v))
        return;
    std::string str = "";
    str += DebugLevelToString(v);
    str += " - ";
    str = message.c_str();
    str += "\n";
    std::cout << str;
}

void cLogSetDebugLevel(DebugLevel v)
{
    currentDebugLevel = v;
}