#include "ButtonStateMachine.h"
int ButtonStateMachine::getState()
{
    return this->state;
}
bool ButtonStateMachine::isPressed()
{
    if (this->state == ButtonStates::STATE_IS_FALLING && this->state == ButtonStates::STATE_CLOSED)
        return true;
    return false;
}
int ButtonStateMachine::nextState(int p){

}