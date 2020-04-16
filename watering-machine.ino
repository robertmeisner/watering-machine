#include <Arduino.h>
#include "src/WateringMachine/Components/PulsePump.h"
#include "src/WateringMachine/Components/Light.h"
#include "src/WateringMachine/Components/MoistureSensor.h"
#include "src/WateringMachine/Utils/CustomLog.h"
#include "src/WateringMachine/WateringMachine.h"
#include "src/WateringMachine/WateringMachineConfig.h"
#include "src/WateringMachine/States/StateFactory.h"
#include "src/WateringMachine/Utils/CommandLine.h"
// #define WATERING_TEST 1
#ifdef WATERING_TEST
#include "src/Firmware/Functions.Test.h"
#else
#include "src/Firmware/Arduino/ControlFunctions.v1.h"
#endif

// config object inistated
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
    const unsigned long ONE_HOUR = 1000 * 60 * 60;
    config.LIGHTING_DURATION = ONE_HOUR * 12;
    config.LIGHTING_INTERVAL = ONE_HOUR * 12;
    config.WATERING_MAX_DURATION = ONE_HOUR;
    config.WATERING_MAX_INTERVAL = ONE_HOUR * 24 * 6;
    config.WATERING_MIN_INTERVAL = ONE_HOUR;
    config.MOISTURE_TRESHOLD = 60;
    config.WATERING_STOP_TRESHOLD = 85;
    cLog("Adding sensors");
    static std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(Sensor1ReadFunc, sensorInitFunc));
    sensors.push_back(MoistureSensor(Sensor2ReadFunc, sensorInitFunc));
    static StateFactory sf;
    cLog("Creating WateringMachine object");
    wateringMachine = new WateringMachine(config, sf, light, pump, sensors);
    cLog("Initiating WateringMachine object");
    wateringMachine->init();
    cLog("Setting up has finished");
};
/**
 * Arduino loop function
 */
void loop()
{
    bool received = getCommandLineFromSerialPort(CommandLine); //global CommandLine is defined in CommandLine.h
    if (received)
        serialCommand(CommandLine); // execute the command
    wateringMachine->tick();
    delay(5000);
};
