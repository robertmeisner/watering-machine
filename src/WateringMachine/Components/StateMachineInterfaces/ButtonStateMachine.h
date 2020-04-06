#include "StateMachine.h"
enum ButtonModes
{
    MODE_PULLUP,
    MODE_PULLDOWN
};
enum ButtonStates
{
    STATE_OPEN,
    STATE_RISING,
    STATE_CLOSED,
    STATE_IS_FALLING
};
enum ButtonCommand
{
    COMMAND_PRESSED,
    COMMAND_RELEASED
};
class ButtonStateMachine : public StateMachine
{
public:
    int state = ButtonStates::STATE_OPEN;
    int getState();
    bool isPressed();
    ~ButtonStateMachine() {} // Destructor
private:
    virtual int nextState(int p) = 0;
};
