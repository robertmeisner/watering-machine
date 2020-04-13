#ifndef SimplePumps_h
#include "StateMachineInterfaces/PumpStateMachine.h"
#define SimplePumps_h

class SimplePump : public PumpStateMachine
{
public:
  /**
   * SimplePump 
   * 
   * @param  {bool(*)()} startFunc        : function used to start hte pump
   * @param  {bool(*)()} stopFunc         : 
   * @param  {bool(*)()=nullptr} initFunc : 
   */
  SimplePump(bool (*startFunc)(), bool (*stopFunc)(), bool (*initFunc)() = nullptr);

  bool start();
  bool stop();
  unsigned long getDurationSinceLastChange();
  bool init();
  bool tick(){};

protected:
  bool (*_startFunc)();
  bool (*_stopFunc)();
  bool (*_initFunc)();
  unsigned long sinceLastChangeChrono;
};

#endif