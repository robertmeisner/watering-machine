#include "../../Base.hh"
#include"../../Firmware/ControlFunctions.Test.h"
#include"../../helpers/MiddlewareTest.h"
#include <WateringMachine/WateringMachine.h>
#include <WateringMachine/WateringMachineConfig.h>
#include <WateringMachine/Components/Light.h>
#include <WateringMachine/Components/PulsePump.h>
#include <WateringMachine/Components/MoistureSensor.h>
#include <WateringMachine/Middleware/MiddlewareInterface.h>
#include <WateringMachine/States/StateFactory.h>
#include <vector>
static Light light(lightOnFunc, lightOffFunc, lightInitFunc, timeFunction);
static PulsePump pump(startPumpFunc, stopPumpFunc, initPumpFunc, timeFunction); //static so they wont be deleted after setup is detroyed
static std::vector<MoistureSensor*> sensors;
static std::vector<MiddlewareInterface*> middlewares;
static StateFactory sf;
void testDurationCount() {
    middlewares.push_back(new MiddlewareTest());
    WateringMachine* wateringMachine= new WateringMachine(new WateringMachineConfig(), &sf, &light, &pump, &sensors, &middlewares);
    wateringMachine->init();
    
}
int main(int, char**)
{
    testDurationCount();

}