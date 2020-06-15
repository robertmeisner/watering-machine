#include <Arduino.h>
// Include custom log library
#include "src/WateringMachine/Utils/CustomLog.h"
// Include components
#include "src/WateringMachine/Components/PulsePump.h"
#include "src/WateringMachine/Components/Light.h"
#include "src/WateringMachine/Components/MoistureSensor.h"
// include State factory (class geenrating states of Watering Machine)
#include "src/WateringMachine/States/StateFactory.h"
// include config class
#include "src/WateringMachine/WateringMachineConfig.h"
// include Watering Machine
#include "src/WateringMachine/WateringMachine.h"

#include "src/WateringMachine/Utils/CommandLine.h"
// include Control Functions used to interface with hardware. Those are injected into Components' constructors.
// #define WATERING_TEST 1
#ifdef WATERING_TEST
#include "src/Firmware/Functions.Test.h"
#else
#include "src/Firmware/Arduino/ControlFunctions.v1.h"
#endif

// config object instantiated
WateringMachineConfig config;
// pointer to WateringMachine
WateringMachine *wateringMachine;
// create pump object
static PulsePump pump(startPumpFunc, stopPumpFunc, initPumpFunc); //static so they wont be deleted after setup is detroyed
// create light object
static Light light(lightOnFunc, lightOffFunc, lightInitFunc);
/**
 * Logic of each command.
 * @param  {char*} commandLine : 
 * @return {bool}              : 
 */
bool serialCommand(char *commandLine)
{
    char *ptrToCommandName = strtok(commandLine, delimiters);

    if (strcmp(ptrToCommandName, "turnLight") == 0)
    {
        wateringMachine->turnLight();
    }
    else if (strcmp(ptrToCommandName, "turnIdle") == 0)
    {
        wateringMachine->turnIdle();
    }
    else if (strcmp(ptrToCommandName, "turnWatering") == 0)
    {
        wateringMachine->turnWatering();
    }
    else
    {
        nullCommand(ptrToCommandName);
    }
    return true;
}
/**
 * Arduno setup function
 */
void setup()
{
    // initialize the serial communication:
    Serial.begin(115200);
    cLog("Setting up the Watering Machine");
    const unsigned long ONE_HOUR = 1000 * 60 * 60; // hour constant

    config.LIGHTING_DURATION = ONE_HOUR * 8;          // How long lighting session should last
    config.LIGHTING_INTERVAL = ONE_HOUR * 16;         // Interval between lighting sessions
    config.WATERING_MAX_DURATION = ONE_HOUR / 2;      // How long watering should last
    config.WATERING_MAX_INTERVAL = ONE_HOUR * 24 * 7; // Maximal interval between waterings. After that time, watering will start even if avarage moisture level from sensors is over the MOISTURE_TRESHOLD
    config.WATERING_MIN_INTERVAL = ONE_HOUR;          // Minimal interval between waterings. After watering is done it won't start again, before WATERING_MIN_INTERVAL has passed,even if avarage moisture level from sensors is below the MOISTURE_TRESHOLD
    config.MOISTURE_TRESHOLD = 50;                    //if avarage moisture level from sensors is below the MOISTURE_TRESHOLD watering starts
    config.WATERING_STOP_TRESHOLD = 90;               //watering will stop if avarage moisture level from sensors reaches that value
    cLog("Adding sensors");
    // Create sensor objects and add them to a vector
    static std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(Sensor1ReadFunc, sensorInitFunc));
    sensors.push_back(MoistureSensor(Sensor2ReadFunc, sensorInitFunc));
    // initialize StafeFactory object
    static StateFactory sf;
    //create a WateringMachine object
    cLog("Creating WateringMachine object");
    wateringMachine = new WateringMachine(config, sf, light, pump, sensors);
    //init the WateringMachine
    cLog("Initiating WateringMachine object");
    wateringMachine->init();
    cLog("Setting up has finished");
};
/**
 * Arduino loop function
 */
void loop()
{
    // handle Commands on Serial Port
    bool received = getCommandLineFromSerialPort(CommandLine); //global CommandLine is defined in CommandLine.h
    if (received)
        serialCommand(CommandLine); // execute the command
    // call tick function handle WateringMachine logic
    wateringMachine->tick();
    // delay 5s
    delay(5000);
};
