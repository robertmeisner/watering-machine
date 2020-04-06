#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
//abstract class
class StateMachine
{
public:
  //initialize the machine
  inline virtual bool init() = 0;
  inline virtual bool tick() =0;
  virtual ~StateMachine(){}; // Destructor
  int state = -1;

protected:
  virtual int nextState(int command) = 0;

private:
};
#endif