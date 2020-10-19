#include "WateringMachineStateBase.h"
WateringMachineStateBase::WateringMachineStateBase( ) {}
WateringMachineStateBase::WateringMachineStateBase( WateringMachine* wm) : context(wm){}
const char* WateringMachineStateBase::getName() { return "";  }
bool WateringMachineStateBase::handleWatering(){ return true; };
bool WateringMachineStateBase::handleLighting(){ return true; };
bool WateringMachineStateBase::handleIdle(){ return true; };
bool WateringMachineStateBase::init(){ return true; };
bool WateringMachineStateBase::tick(){ return true; };
bool WateringMachineStateBase::setContext(WateringMachine *cont){
    this->context=cont;
    return true;
};