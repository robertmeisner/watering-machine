#ifndef ARDUINO_LOGGING_MIDDLEWARE_H
#define ARDUINO_LOGGING_MIDDLEWARE_H
#include "../../../WateringMachine/WateringMachineStats.h"
#include "../../../WateringMachine/WateringMachineConfig.h"
#include "../../../WateringMachine/WateringMachineConfig.h"
#include "WateringMachineResources.h"
#include "Arduino.h"
#define ARDUINOJSON_ENABLE_STD_STRING 1
#include <ArduinoJson.h>

std::string configAndStatsToJson(std::string eventName, WateringMachineConfig *config, WateringMachineStats *stats)
{
}
struct MQTTRequestResponse
{
    MQTTRequestResponse() : config(nullptr), stats(nullptr), resources(nullptr)
    {
    }
    std::string event;
    std::string command;
    std::string timestamp;
    WateringMachineConfig *config;
    WateringMachineStats *stats;
    WateringMachineResources *resources;
};
std::string serializeMQTT(MQTTRequestResponse *jsonResponse)
{
    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<256> doc;

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
        stats["lightOn"] = jsonResponse->stats->lightOn;
        stats["wateringOn"] = jsonResponse->stats->wateringOn;
        stats["stateName"] = jsonResponse->stats->stateName;

        JsonArray moistureSensorActive = stats.createNestedArray("moistureSensorActive");
        for (int i = 0; i <= (sizeof(jsonResponse->stats->moistureSensorActive) / sizeof(jsonResponse->stats->moistureSensorActive[0])); i++)
        {
            moistureSensorActive[i] = jsonResponse->stats->moistureSensorActive[i];
        }
        JsonArray moistureSensorReadings = stats.createNestedArray("moistureSensorReadings");
        for (int i = 0; i <= (sizeof(jsonResponse->stats->moistureSensorReadings) / sizeof(jsonResponse->stats->moistureSensorReadings[0])); i++)
        {
            moistureSensorReadings[i] = jsonResponse->stats->moistureSensorReadings[i];
        }
    }
    JsonObject resources = doc.createNestedObject("resources");

    if (jsonResponse->stats != nullptr)
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
        Serial.println(F("Failed to write to file"));
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
MQTTRequestResponse *deserializeMQTT(unsigned char* json, int length)
{

//std::string json=
    MQTTRequestResponse *jsonResponse = new MQTTRequestResponse();

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        Serial.println(F("Failed to read file, using default configuration"));
    }
    // jsonResponse->event = doc['event'];

    //strlcpy(jsonResponse->event,                // <- destination
    //      doc["event"] | jsonResponse->event, // <- source
    //     sizeof(jsonResponse->event));       // <- destination's capacity

    jsonResponse->event = doc['event'] | jsonResponse->event;
    jsonResponse->command = doc['command'] | jsonResponse->command;
    if (doc['config'])
    {
        WateringMachineConfig *config = new WateringMachineConfig();
        config->LIGHTING_DURATION = doc['config']["LIGHTING_DURATION"] | config->LIGHTING_DURATION;
        config->LIGHTING_INTERVAL = doc['config']["LIGHTING_INTERVAL"] | config->LIGHTING_INTERVAL;
        config->MOISTURE_MEASUREMENT_INTERVAL = doc['config']["MOISTURE_MEASUREMENT_INTERVAL"] | config->MOISTURE_MEASUREMENT_INTERVAL;
        config->MOISTURE_TRESHOLD = doc['config']["MOISTURE_TRESHOLD"] | config->MOISTURE_TRESHOLD;
        config->WATERING_MAX_DURATION = doc['config']["WATERING_MAX_DURATION"] | config->WATERING_MAX_DURATION;
        config->WATERING_MAX_INTERVAL = doc['config']["WATERING_MAX_INTERVAL"] | config->WATERING_MAX_INTERVAL;
        config->WATERING_MIN_INTERVAL = doc['config']["WATERING_MIN_INTERVAL"] | config->WATERING_MIN_INTERVAL;
        config->WATERING_STOP_TRESHOLD = doc['config']["WATERING_STOP_TRESHOLD"] | config->WATERING_STOP_TRESHOLD;
        jsonResponse->config = config;
    }
    else
    {
        jsonResponse->config = nullptr;
    }
    if (doc['config'])
    {
        jsonResponse->resources = new WateringMachineResources();
        jsonResponse->resources->freeRAM = doc['resources']["freeRAM"] | jsonResponse->resources->freeRAM;
    }
    else
    {
        jsonResponse->config = nullptr;
    }
    return jsonResponse;

    // Copy values from the JsonDocument to the Config
    // config.port = doc["port"] | 2731;
    //strlcpy(config.hostname,                 // <- destination
    //       doc["hostname"] | "example.com", // <- source
    //      sizeof(config.hostname));        // <- destination's capacity
}
#endif