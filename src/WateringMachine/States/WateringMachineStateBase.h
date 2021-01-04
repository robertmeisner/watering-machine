
#include "StateTypeEnum.h"
#ifndef W_M_STATE_BASE_H
#define W_M_STATE_BASE_H
class WateringMachine;
/**
 * Base abstract class describing a contract for all Watering Machine State subclasses.
 * Contains abstract "handle" methods which serve as a transition from one state to another.
 */
class WateringMachineStateBase
{
public:
  /**
   * WateringMachineStateBase constructor
   * 
   * Watering Machine pointer can be set after  state instantiation using setContext(WateringMachine *context) method.
   */
  WateringMachineStateBase();
  /**
   * WateringMachineStateBase constructor
   * 
   * @param  {WateringMachine*} context : wateringMachine pointer 
   */
  WateringMachineStateBase(WateringMachine *context);
  // Class destructor for WateringMachineStateBase (Declared as virtual)
  virtual ~WateringMachineStateBase();
  //maybe do it pure virtual?
  virtual const char *getName();
  ;
  /**
   * Handles the change to  Watering State
   * @return {bool}  : true if state has been changed, false if state change wasn't possible.
   */
  virtual bool handleWatering();
  
  /**
   * Handles the change to Lighting State
   * @return {bool}  : true if state has been changed, false if state change wasn't possible.
   */
  virtual bool handleLighting();
  /**
   * Handles the change to Idle State
   * @return {bool}  : true if state has been changed, false if state change wasn't possible.
   */
  virtual bool handleIdle();
  
  /**
   * Initiates the state
   * @return {bool}  : 
   */
  virtual bool init();
  /**
   * Tick method simulates a passage of time.
   * Enables implementation timers or timeouts.
   * @return {bool}  : 
   */
  virtual bool tick();
  /**
   * Sets the context WateringMachine of the state. Useful if can't pass WateringMachine in state's constructor.
   * @param  {WateringMachine*} context : 
   * @return {bool}                     : 
   */
  virtual bool setContext(WateringMachine *context);
  /**
   * Type of the State
   */
  StateType type = StateType::UNDEFINED_STATE;

protected:
  WateringMachine *context;
};
#endif