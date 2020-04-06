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
class PumpStateMachine : public StateMachine
{
public:
    int state = PumpStates::STATE_OFF;
    ~PumpStateMachine() {} // Destructor
    inline virtual bool start() = 0;
    inline virtual bool stop() = 0;

protected:
    int nextState(int command); // Needs to be implemented by each subclass
};
