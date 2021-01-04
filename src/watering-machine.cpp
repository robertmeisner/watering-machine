#include <Arduino.h>
#define WATERING_ESP8266 1
#ifdef WATERING_ESP32
#include <WiFi.h>
#endif
#ifdef WATERING_ESP8266
#include <ESP8266WiFi.h>
#endif

// Include custom log library

#include "WateringMachine/Utils/DebugLevelEnum.h"
#include "WateringMachine/Utils/CustomLog.h"
// Include components
#include "WateringMachine/Components/PulsePump.h"
#include "WateringMachine/Components/Light.h"
#include "WateringMachine/Components/MoistureSensor.h"
// include State factory (class geenrating states of Watering Machine)
#include "WateringMachine/States/StateFactory.h"
// include config class
#include "WateringMachine/WateringMachineConfig.h"
// include Watering Machine
#include "WateringMachine/WateringMachine.h"

#include "Firmware/Arduino/ArduinoCommandLine.h"
#include "Firmware/Arduino/Middleware/MQTT/ArduinoMQTTMiddleware.h"
#include "Firmware/Arduino/Middleware/Logging/ArduinoLoggingMiddleware.h"
// include Control Functions used to interface with hardware. Those are injected into Components' constructors.
// #define WATERING_TEST 1
#ifdef WATERING_TEST
#include "Firmware/Functions.Test.h"
#else
#include "Firmware/Arduino/ControlFunctions.esp8266.h"
#endif
#include "watering-machine.config.h"
static WiFiClient wifiClient;

// config object instantiated
WateringMachineConfig config;
// pointer to WateringMachine
WateringMachine *wateringMachine;
// create pump object
static PulsePump pump(startPumpFunc, stopPumpFunc, initPumpFunc, timeFunction); //static so they wont be deleted after setup is detroyed
// create light object
static Light light(lightOnFunc, lightOffFunc, lightInitFunc, timeFunction);
/**
 * Logic of each command.
 * @param  {char*} commandLine : 
 * @return {bool}              : 
 */
bool serialCommand(char *commandLine, WateringMachineConfig *config = nullptr)
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
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, WifiPassword);
    delay(2000);
    int i;
    for (i = 1; i < 10; i++)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connecting to WiFi..");
            Serial.println(WiFi.status());
        }
    }

    cLog("Setting up the Watering Machine");

    cLog("Adding sensors");
    // Create sensor objects and add them to a vector
    static std::vector<MoistureSensor *> sensors;
    sensors.push_back(new MoistureSensor(Sensor1ReadFunc, sensorInitFunc));
    sensors.push_back(new MoistureSensor(Sensor2ReadFunc, sensorInitFunc));
    sensors.push_back(new MoistureSensor(Sensor3ReadFunc, sensorInitFunc));
    sensors.push_back(new MoistureSensor(Sensor4ReadFunc, sensorInitFunc));
    // initialize StafeFactory object
    static StateFactory sf;
    //create a WateringMachine object
    cLog("Creating WateringMachine object");
    static std::vector<MiddlewareInterface *> middlewares;
    middlewares.push_back(new ArduinoLoggingMiddleware());
    middlewares.push_back(new ArduinoMQTTMiddleware(MQTTHost, MQTTPort, MQTTUser, MQTTPass, &wifiClient, MQTTopicIn, MQTTTopicOut));
    wateringMachine = new WateringMachine(&config, &sf, &light, &pump, &sensors, &middlewares);

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
    int i;
    for (i = 1; i < 10; i++)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            //WiFi.disconnect();
            //WiFi.mode(WIFI_STA);
            delay(1000);
            //WiFi.begin(SSID, WifiPassword);

            Serial.println("Connecting to WiFi..");
            Serial.println(WiFi.status());
        }
    }
    // handle Commands on Serial Port
    bool received = getCommandLineFromSerialPort(CommandLine); //global CommandLine is defined in CommandLine.h
    if (received)
        serialCommand(CommandLine, nullptr); // execute the command
    // call tick function handle WateringMachine logic
    wateringMachine->tick();
    // delay 5s
    delay(5000);
};
