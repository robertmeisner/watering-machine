#include "StateMachine.h"
enum MotorStates
{
    STATE_OFF,
    STATE_ON
};
enum MotorCommand
{
    COMMAND_START,
    COMMAND_STOP

};
/**
 * Abstract State Machine for Motor Devices.
 * Implements generic nextState(int command) method.
 */
class MotorStateMachine : public StateMachine
{
public:
    int state = MotorStates::STATE_OFF;
    ~MotorStateMachine() {} // Destructor
    
    /**
     * Starts the Motor
     * @param  {int} speed : 
     * @return {bool}      :  true if succesful, false otherwise
     */
    inline virtual bool start(int speed) = 0;
    /**
     * Changes a speed of the motor. 
     * @param  {int} speed : Speed of the motor. Ranges from 0 to 100.
     * @return {bool}      :  true if succesful, false otherwise
     */
    inline virtual bool changeSpeed(int speed) = 0;
    /**
     * Stops the motor
     * @return {bool}  :  true if succesful, false otherwise
     */
    inline virtual bool stop() = 0;

protected:
    int nextState(int command);
};
