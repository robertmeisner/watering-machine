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
class MotorStateMachine : public StateMachine
{
public:
    int state = MotorStates::STATE_OFF;
    ~MotorStateMachine() {} // Destructor
    inline virtual bool start(int speed) = 0;
    inline virtual bool changeSpeed(int speed) = 0;
    inline virtual bool stop() = 0;

protected:
    int nextState(int command); // Needs to be implemented by each subclass
};
