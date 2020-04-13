#include "StateMachine.h"
enum PumpStates
{
    STATE_OFF,
    STATE_ON
};
enum PumpCommand
{
    COMMAND_START,
    COMMAND_STOP

};
/**
 * Abstract State Machine for Pump Devices.
 * Implements generic nextState(int command) method.
 */
class PumpStateMachine : public StateMachine
{
public:
    int state = PumpStates::STATE_OFF;
    ~PumpStateMachine() {} // Destructor
    /**
     * Starts the pump 
     * @return {bool}  : true if succesful, false otherwise
     */
    inline virtual bool start() = 0;
    /**
     * Stops the pump
     * @return {bool}  : true if succesful, false otherwise
     */
    inline virtual bool stop() = 0;

protected:
    int nextState(int command); 
};
