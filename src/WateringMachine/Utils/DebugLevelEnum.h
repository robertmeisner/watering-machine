#ifndef DEBUG_LEVEL_ENUM_H
#define DEBUG_LEVEL_ENUM_H
enum class DebugLevel : unsigned char
{
    OFF = 0x01,
    FATAL = 0x03,
    ERROR = 0x05,
    WARNING = 0x10,
    INFO = 0x20,
    DEBUG = 0x40,
    VERBOSE = 0x80,
    ALL = 0x99
};
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
#endif