#include "MiddlewareInterface.h"
#include <iostream>
MiddlewareInterface::MiddlewareInterface() {
}
bool MiddlewareInterface::init(WateringMachine* wm) {
    std::cout << ("MiddlewareInterface init.");
    return false;
 }

bool MiddlewareInterface::tick(WateringMachine* wm) {
    std::cout << ("MiddlewareInterface tick.");
    return false;
 }

 bool MiddlewareInterface::stateChange(WateringMachine* wm,WateringMachineStateBase* oldState, WateringMachineStateBase* nextState) {
     std::cout << ("MiddlewareInterface stateChange.");
     return false;
}
