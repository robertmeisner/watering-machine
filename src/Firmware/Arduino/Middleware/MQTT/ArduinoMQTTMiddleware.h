#ifndef MQTTMIDDLEWARE_STATE_H
#define MQTTMIDDLEWARE_STATE_H
#include "../../../../WateringMachine/Middleware/MiddlewareInterface.h"
#define WATERING_ESP8266 1
#ifdef WATERING_ESP32
#include <WiFi.h>
#endif
#ifdef WATERING_ESP8266
#include <ESP8266WiFi.h>
#endif
#include <Arduino.h>
class WateringMachine;
//class WiFiClient;
class PubSubClient;
class MQTTRequestResponse;
/**
 * During Watering state pumps are turned on until defined moisture thresholds are met.
 */
class ArduinoMQTTMiddleware : public MiddlewareInterface
{

private:
    void callback(char *topic, byte *payload, unsigned int length);
    void setInfo(MQTTRequestResponse *mqtt_req);
    bool publishStats();
    WateringMachine *wateringMachine;
    WiFiClient *wifiClient;
    PubSubClient *client;
    const char *mqttServer;
    int mqttPort;
    const char *mqttUser;
    const char *mqttPassword;

public:
    ArduinoMQTTMiddleware(const char *mqttServer,
                          int mqttPort,
                          const char *mqttUser,
                          const char *mqttPassword,
                          WiFiClient *espClient, const char *mqttTopicIn, const char *mqttTopicOut);

    bool init(WateringMachine *wm);
    bool tick();
    void log(char *message, int logType);
    bool stateChange(WateringMachineStateBase *oldState, WateringMachineStateBase *nextState);
    boolean reconnect();
    const char *mqttTopicIn = "topicIn";
    const char *mqttTopicOut = "topicOut";
};
#endif