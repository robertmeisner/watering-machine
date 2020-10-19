#include "../../Base.hh"
#include"../../Firmware/ControlFunctions.Test.h"
#include <WateringMachine/Components/Light.h>
static Light light(lightOnFunc, lightOffFunc, lightInitFunc,timeFunction);

void testInit(){
    WM_TEST_BEGIN("Light: init");
    WM_ASSERT_THROW(light.init() == true);
    WM_TEST_END();
}
void testTurnOn(){
    WM_TEST_BEGIN("Light: turnOn");
    WM_ASSERT_THROW(light.turnOn() == true);
    WM_ASSERT_THROW(light.isOn()==true)
    WM_TEST_END();
}
void testTurnOff() {
    WM_TEST_BEGIN("Light: turnOff");
    WM_ASSERT_THROW(light.turnOff() == true);
    WM_ASSERT_THROW(light.isOn() == false)
    WM_TEST_END();
}
void testDurationCount() {
    WM_TEST_BEGIN("Light: testDurationCount");
    timeFunctionValue = 1000;
    light.init();
    light.turnOff();
    WM_ASSERT_EQUAL(light.getDurationSinceLastChange(),0);
    timeFunctionValue = 9500;
    light.turnOn();
    timeFunctionValue = 10000;
    WM_ASSERT_EQUAL(light.getDurationSinceLastChange(), (500));
    WM_TEST_END();
}
int main( int, char** )
{
  testInit();
  testTurnOn();
  testTurnOff();
  testDurationCount();

}