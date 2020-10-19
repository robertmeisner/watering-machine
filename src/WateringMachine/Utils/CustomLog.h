#ifndef CustomDebug_h
#include "./DebugLevelEnum.h"
#include <string>
#include <iostream>
#define CustomDebug_h
static DebugLevel currentDebugLevel = DebugLevel::INFO;
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
 * @param  {std::string} message : 
 * @param  {DebugLevel} v        : 
 */
void cLog(const std::string &message, DebugLevel v = DebugLevel::INFO);
#endif