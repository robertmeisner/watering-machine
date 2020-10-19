#include "SimpleMotor.h"
#include "../Utils/CustomLog.h"
// IMPLEMENTATION
bool SimpleMotorInitMockFunc()
{
    return true;
}
SimpleMotor::SimpleMotor(bool (*startFunc)(int), bool (*stopFunc)(), bool (*changeSpeedFunc)(int), bool (*initFunc)(), unsigned long (*timeFunc)() , int initialSpeed) : MotorStateMachine()
{
    this->_timeFunc = timeFunc;
    this->_startFunc = startFunc;
    this->_stopFunc = stopFunc;
    this->_changeSpeedFunc = changeSpeedFunc;
    if (initFunc == nullptr)
    {
        this->_initFunc = SimpleMotorInitMockFunc;
    }
    else
    {
        this->_initFunc = initFunc;
    }
    this->_speed = initialSpeed;
}
bool SimpleMotor::start(int speed)
{
    cLog("Starting the motor");

    this->_startFunc(speed);
    this->nextState(MotorCommand::COMMAND_START);
    this->sinceLastChangeChrono = this->_timeFunc();

    return this->state == MotorStates::STATE_ON;
}

bool SimpleMotor::changeSpeed(int speed)
{
    if (this->state == MotorStates::STATE_OFF)
    {
        if (this->_changeSpeedFunc(speed))
        {
            this->_speed = speed;

            if (this->state == MotorStates::STATE_ON && speed == 0)
            {
                return this->stop();
            }
        }
    }
    return false;
}
bool SimpleMotor::stop()
{

    if (this->_stopFunc())
    {
        this->sinceLastChangeChrono = this->_timeFunc();
        if (this->nextState(MotorCommand::COMMAND_STOP) == MotorStates::STATE_OFF)
            return true;
    }
    cLog("Couldn't stop the motor");
    return false;
}
unsigned long SimpleMotor::getDurationSinceLastChange()
{
    return this->_timeFunc() - this->sinceLastChangeChrono;
}

bool SimpleMotor::init()
{
    cLog("Initiating SimpleMotor");
    return this->_initFunc();
}