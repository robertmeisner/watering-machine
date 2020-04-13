#ifndef CustomDebug_h
#include <Arduino.h>
#define CustomDebug_h
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
static DebugLevel currentDebugLevel = DebugLevel::INFO;
inline const char *DebugLevelToString(DebugLevel v);
/**
 * Sets a Debug Level. Used to diable  logging of low level messages.
 * @param  {DebugLevel} v : 
 */
void cLogSetDebugLevel(DebugLevel v);
/**
 * 
 * @param  {char*} message : 
 * @param  {DebugLevel} v  : 
 */
void cLog(const char *message, DebugLevel v = DebugLevel::INFO);
/**
 * 
 * @param  {String} message : 
 * @param  {DebugLevel} v   : 
 */
void cLog(const String message, DebugLevel v = DebugLevel::INFO);
/**
 * 
 * @param  {std::string} message : 
 * @param  {DebugLevel} v        : 
 */
void cLog(const std::string &message, DebugLevel v = DebugLevel::INFO);
#endif