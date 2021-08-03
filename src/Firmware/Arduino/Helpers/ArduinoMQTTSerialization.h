#ifndef ARDUINO_LOGGING_MIDDLEWARE_H
#define ARDUINO_LOGGING_MIDDLEWARE_H
#include "../../../WateringMachine/WateringMachineStats.h"
#include "../../../WateringMachine/WateringMachineConfig.h"
#include "../../../WateringMachine/WateringMachineConfig.h"
#include "WateringMachineResources.h"
#include <iostream>
#include "Arduino.h"
#define ARDUINOJSON_ENABLE_STD_STRING 1
// #define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

char *unconstchar(const char *s)
{
    if (!s)
        return NULL;
    int i;
    char *res = NULL;
    res = (char *)malloc(strlen(s) + 1);
    if (!res)
    {
        //(stderr, "Memory Allocation Failed! Exiting...\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (i = 0; s[i] != '\0'; i++)
        {
            res[i] = s[i];
        }
        res[i] = '\0';
        return res;
    }
}
std::string configAndStatsToJson(std::string eventName, WateringMachineConfig *config, WateringMachineStats *stats)
{
    return "";
}
struct MQTTRequestResponse
{
    MQTTRequestResponse() : event(nullptr), command(nullptr), timestamp(nullptr),config(nullptr), stats(nullptr), resources(nullptr)
    
    {
    }
    char *event;
    char *command;
    char *timestamp;
    WateringMachineConfig *config;
    WateringMachineStats *stats;
    WateringMachineResources *resources;
};
std::string serializeMQTT(MQTTRequestResponse *jsonResponse)
{
    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<1024> doc;

    // Set the values in the document
    doc["event"] = jsonResponse->event;
    doc["command"] = jsonResponse->command;

    // Add an array.
    JsonObject config = doc.createNestedObject("config");
    if (jsonResponse->config != nullptr)
    {

        config["LIGHTING_DURATION"] = jsonResponse->config->LIGHTING_DURATION;
        config["LIGHTING_INTERVAL"] = jsonResponse->config->LIGHTING_INTERVAL;
        config["MOISTURE_MEASUREMENT_INTERVAL"] = jsonResponse->config->MOISTURE_MEASUREMENT_INTERVAL;
        config["MOISTURE_TRESHOLD"] = jsonResponse->config->MOISTURE_TRESHOLD;
        config["WATERING_MAX_DURATION"] = jsonResponse->config->WATERING_MAX_DURATION;
        config["WATERING_MAX_INTERVAL"] = jsonResponse->config->WATERING_MAX_INTERVAL;
        config["WATERING_MIN_INTERVAL"] = jsonResponse->config->WATERING_MIN_INTERVAL;
        config["WATERING_STOP_TRESHOLD"] = jsonResponse->config->WATERING_STOP_TRESHOLD;
    }
    JsonObject stats = doc.createNestedObject("stats");
    if (jsonResponse->stats != nullptr)
    {
        stats["averageMoisture"] = jsonResponse->stats->averageMoisture;
        stats["waterLevel"] = jsonResponse->stats->waterLevel;
        stats["lightOn"] = jsonResponse->stats->lightOn;
        stats["pumpOn"] = jsonResponse->stats->pumpOn;
        stats["lightDurationSinceLastChange"] = jsonResponse->stats->lightDurationSinceLastChange;
        stats["pumpDurationSinceLastChange"] = jsonResponse->stats->pumpDurationSinceLastChange;
        stats["state"] = jsonResponse->stats->state;
        stats["statePrevious"] = jsonResponse->stats->statePrevious;

        JsonArray moistureSensorActive = stats.createNestedArray("moistureSensorActive");
        for (unsigned int i = 0; i < (sizeof(jsonResponse->stats->moistureSensorActive) / sizeof(jsonResponse->stats->moistureSensorActive[0])); i++)
        {
            moistureSensorActive[i] = jsonResponse->stats->moistureSensorActive[i];
            std::cout << jsonResponse->stats->moistureSensorActive[i];
            std::cout << "\n";
        }
        std::cout << (sizeof(jsonResponse->stats->moistureSensorActive) / sizeof(jsonResponse->stats->moistureSensorActive[0]));
        std::cout << "  number of moistureSensorActive \n";
        std::cout << (sizeof(jsonResponse->stats->moistureSensorActive));
        std::cout << "  size of\n";
        JsonArray moistureSensorReadings = stats.createNestedArray("moistureSensorReadings");

        std::cout << (sizeof(jsonResponse->stats->moistureSensorReadings) / sizeof(jsonResponse->stats->moistureSensorReadings[0]));
        std::cout << "  number of moistureSensorReadings \n";
        std::cout << (sizeof(jsonResponse->stats->moistureSensorReadings));
        std::cout << "  size of\n";
        for (unsigned int i = 0; i < (sizeof(jsonResponse->stats->moistureSensorReadings) / sizeof(jsonResponse->stats->moistureSensorReadings[0])); i++)
        {
            moistureSensorReadings[i] = jsonResponse->stats->moistureSensorReadings[i];
        }
    }
    JsonObject resources = doc.createNestedObject("resources");

    if (jsonResponse->resources != nullptr)
    {
        resources["freeRAM"] = jsonResponse->resources->freeRAM;
    }
    //JsonArray data = doc.createNestedArray("data");
    //data.add(48.756080);
    //data.add(2.302038);

    // Serialize JSON to file
    std::string jsonString = "";
    if (serializeJson(doc, jsonString) == 0)
    {
        Serial.println(F("Failed to serialize Json"));
    }
    return jsonString;
}
/*std::string convertToString(char* a, int size) 
{ 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} */
MQTTRequestResponse *deserializeMQTT(MQTTRequestResponse *jsonResponse, unsigned char *json, int length)
{
    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    // StaticJsonDocument<1024> doc;
    DynamicJsonDocument object(2024);

    // Deserialize the JSON document

    DeserializationError error = deserializeJson(object, json); //DeserializationOption::NestingLimit(20)
    switch (error.code())
    {
    case DeserializationError::Ok:
        Serial.print(F("Deserialization succeeded"));
        break;
    case DeserializationError::InvalidInput:
        Serial.print(F("Invalid input!"));
        break;
    case DeserializationError::NoMemory:
        Serial.print(F("Not enough memory"));
        break;
    default:
        Serial.print(F("Deserialization failed"));
        break;
    };
    // extract the data
    //JsonObject object = doc.to<JsonObject>();

    Serial.println("deserializeMQTT");
    // std::string jsonString = "";
    // serializeJson(object,jsonString);
    jsonResponse->command = unconstchar(object["command"]);
    jsonResponse->event = unconstchar(object["event"]);

    if (object["config"])
    {
        Serial.println("New config detected");
        WateringMachineConfig *config = new WateringMachineConfig();
        config->LIGHTING_DURATION = object["config"]["LIGHTING_DURATION"] | config->LIGHTING_DURATION;
        config->LIGHTING_INTERVAL = object["config"]["LIGHTING_INTERVAL"] | config->LIGHTING_INTERVAL;
        config->MOISTURE_MEASUREMENT_INTERVAL = object["config"]["MOISTURE_MEASUREMENT_INTERVAL"] | config->MOISTURE_MEASUREMENT_INTERVAL;
        config->MOISTURE_TRESHOLD = object["config"]["MOISTURE_TRESHOLD"] | config->MOISTURE_TRESHOLD;
        config->WATERING_MAX_DURATION = object["config"]["WATERING_MAX_DURATION"] | config->WATERING_MAX_DURATION;
        config->WATERING_MAX_INTERVAL = object["config"]["WATERING_MAX_INTERVAL"] | config->WATERING_MAX_INTERVAL;
        config->WATERING_MIN_INTERVAL = object["config"]["WATERING_MIN_INTERVAL"] | config->WATERING_MIN_INTERVAL;
        config->WATERING_STOP_TRESHOLD = object["config"]["WATERING_STOP_TRESHOLD"] | config->WATERING_STOP_TRESHOLD;
        jsonResponse->config = config;
    }
    else
    {
        Serial.println("No config detected");
        jsonResponse->config = nullptr;
    }
    std::string jsonString2 = "";
    if (serializeJson(object, jsonString2) == 0)
    {
        Serial.println(F("Failed to serialize Json"));
    }
    Serial.println(jsonString2.c_str());

    JsonObject obj = object.as<JsonObject>();
    for (JsonObject::iterator it = obj.begin(); it != obj.end(); ++it)
    {
        Serial.println(it->key().c_str()); // is a JsonString
        //it->value()                // is a JsonVariant
    }
    // Serial.println(doc["rower"]);
    //Serial.println(doc["rower"]);
    //Serial.println(doc["rower"]); // is a JsonString

    return jsonResponse;

    // Copy values from the JsonDocument to the Config
    // config.port = doc["port"] | 2731;
    //strlcpy(config.hostname,                 // <- destination
    //       doc["hostname"] | "example.com", // <- source
    //      sizeof(config.hostname));        // <- destination's capacity
}
#endif