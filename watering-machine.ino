#include <Arduino.h>
#include "src/WateringMachine/Components/PulsePump.h"
#include "src/WateringMachine/Components/Light.h"
#include "src/WateringMachine/Components/MoistureSensor.h"
#include "src/WateringMachine/Components/MechanicalButton.h"
#include "src/WateringMachine/Utils/CustomLog.h"
#include "src/WateringMachine/WateringMachine.h"
#include "src/WateringMachine/WateringMachineConfig.h"
/*#include "WateringMachineStateBase.h"
#include "LightingState.h"
#include "IdleState.h"
#include "WateringState.h"*/
#include "src/WateringMachine/States/StateFactory.h"
#include "src/WateringMachine/Utils/CommandLine.h"
//#define WATERING_TEST 1

#ifdef WATERING_TEST
#include "src/Firmware/Functions.Test.h"
#else
#include "src/Firmware/Arduino/ControlFunctions.v1.h"
#endif
//undefined reference jesli headers are in folders 
// solution after few hours of research was to put everything into src folder.
//MechanicalButton *mb = new MechanicalButton(12);
//ALWAYS USE h and cpp files!!!!! laways h only declrations and cpp for definiton
//always use ifnotdef def
// dont use Arduino ide to write a code / 
// calling global variables in global scope is not permitted oO //cry
//https://community.blynk.cc/t/error-isr-not-in-iram/37426/16
//ICACHE_RAM_ATTR void mbInterruptHandler(void)
//{
// xc->handleInterrupt();
//}

WateringMachineConfig config;
WateringMachine *wateringMachine;
static PulsePump pump(startPumpFunc, stopPumpFunc, initPumpFunc); //static so they wont be deleted after setup is detroyed
static Light light(lightOnFunc, lightOffFunc, lightInitFunc);
/**
 * 
 * @param  {char*} commandLine : 
 * @return {bool}              : 
 */
bool serialCommand(char *commandLine)
{
    //  print2("\nCommand: ", commandLine);

    char *ptrToCommandName = strtok(commandLine, delimiters);
    //  print2("commandName= ", ptrToCommandName);

    if (strcmp(ptrToCommandName, "turnLight") == 0)
    { //Modify here
        wateringMachine->turnLight();
    }
    else if (strcmp(ptrToCommandName, "turnIdle") == 0)
    { //Modify here
        wateringMachine->turnIdle();
    }
    else if (strcmp(ptrToCommandName, "turnWatering") == 0)
    { //Modify here
        wateringMachine->turnWatering();
    }
    else
    {
        nullCommand(ptrToCommandName);
    }
    return true;
}
void setup()
{
    // initialize the serial communication:
    Serial.begin(115200);
    cLog("Setting up the Watering Machine");
    const unsigned long ONE_HOUR = 1000 * 60 * 60;
    config.LIGHTING_DURATION = ONE_HOUR * 8;
    config.LIGHTING_INTERVAL = ONE_HOUR * 16;
    config.WATERING_MAX_DURATION = ONE_HOUR / 3;
    config.WATERING_MAX_INTERVAL = ONE_HOUR * 24 * 10;
    config.WATERING_MIN_INTERVAL = ONE_HOUR;
    config.MOISTURE_TRESHOLD = 50;
    config.WATERING_STOP_TRESHOLD = 80;
    cLog("Adding sensors");
    static std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(Sensor1ReadFunc, sensorInitFunc)); //strange object creation
    sensors.push_back(MoistureSensor(Sensor2ReadFunc, sensorInitFunc));
    static StateFactory sf;
    cLog("Creating WateringMachine object");
    wateringMachine = new WateringMachine(config, sf, light, pump, sensors); //how to apss sf by reference when no parameters?
    cLog("Initiating WateringMachine object");
    wateringMachine->init();
    cLog("Setting up has finished");
};
void loop()
{
    bool received = getCommandLineFromSerialPort(CommandLine); //global CommandLine is defined in CommandLine.h
    if (received)
        serialCommand(CommandLine);

    wateringMachine->tick();
    delay(5000);
};
