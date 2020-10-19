#include "MiddlewareTest.h"
#include <iostream>
bool MiddlewareTest::init() {
    std::cout << ("MiddlewareTest init.");
    return true;
};

bool MiddlewareTest::tick() {

    std::cout << ("MiddlewareTest tick.");
    return true;
};


bool MiddlewareTest::stateChange(StateType nextState) {
    std::cout << ("MiddlewareTest StateType.");
    return true;
};
