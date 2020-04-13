#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
/**
 * Abstract class describing common interface of all State Machines.
 */
class StateMachine
{
public:
  /**
   * Initiates the state machine object.
   * @return {bool}  : true if initialization is succesfull, false otherwise.
   */
  inline virtual bool init() = 0;
  
  /**
   * Tick method should be run periodically to simulate passage of time.
   * Can be used by StateMachine to evaluate internal clocks (ie. automatic turn off after 6h)
   * @return {bool}  : if 
   */
  inline virtual bool tick() =0;
  virtual ~StateMachine(){}; // Destructor

  int state = -1;

protected:
  /**
   * StateMachine can be given a Command. Command usually initiates a transition to a Next State. 
   * Method implements the transition, changes to the Next State and returns it.
   * Needs to be implemented by subclasses.
   * @param  {int} command : Integer representation ofvcommand to be run on the current state.
   * @return {int}         : return integer representation of the next state.
   */
  virtual int nextState(int command) = 0;

private:
};
#endif