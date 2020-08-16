#include "MiddlewareInterface.h"
MiddlewareInterface::MiddlewareInterface() {}
bool MiddlewareInterface::init(){};
bool MiddlewareInterface::tick(){};
bool MiddlewareInterface::stateChange(StateType nextState){};
bool MiddlewareInterface::setContext(WateringMachine *cont)
{
    this->context = cont;
};