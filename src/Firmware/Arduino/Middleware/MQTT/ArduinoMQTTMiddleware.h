#ifndef MQTTMIDDLEWARE_STATE_H
#define MQTTMIDDLEWARE_STATE_H
#include "../../../../WateringMachine/Middleware/MiddlewareInterface.h"
#include <Arduino.h>
class WateringMachine;
class WiFiClient;
class PubSubClient;

/**
 * During Watering state pumps are turned on until defined moisture thresholds are met.
 */
class ArduinoMQTTMiddleware : public MiddlewareInterface
{
public:
    ArduinoMQTTMiddleware(char *mqttServer,
                   int mqttPort,
                   char *mqttUser,
                   char *mqttPassword,
                   WiFiClient *espClient,char *mqttTopicIn,char *mqttTopicOut);
   
    bool init(WateringMachine* wm);
    bool tick();
    void log(char *message, int logType);
    bool stateChange(WateringMachineStateBase* oldState, WateringMachineStateBase* nextState);
    char *mqttTopicOut="topicOut";
    char *mqttTopicIn="topicIn";
private:
    void callback(char *topic, byte *payload, unsigned int length);
    WateringMachine *wateringMachine;
    WiFiClient *wifiClient;
    PubSubClient *client;
    char *mqttServer;
    int mqttPort;
    char *mqttUser;
    char *mqttPassword;
};
#endif