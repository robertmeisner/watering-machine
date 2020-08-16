#ifndef MQTTMIDDLEWARE_STATE_H
#define MQTTMIDDLEWARE_STATE_H
#include "../MiddlewareInterface.h"
#include <PubSubClient.h>
class WateringMachine;
class WiFiClient;
/**
 * During Watering state pumps are turned on until defined moisture thresholds are met.
 */
class MQTTMiddleware : public MiddlewareInterface
{
public:
    MQTTMiddleware(char *mqttServer,
                   int mqttPort,
                   char *mqttUser,
                   char *mqttPassword,
                   WiFiClient &espClient);
   
    bool init();
    bool tick();
    void log(char *message, int logType);
    bool stateChange(StateType nextState);

private:
    void callback(char *topic, byte *payload, unsigned int length);
    WiFiClient &wifiClient;
    PubSubClient client;
    char *mqttServer;
    int mqttPort;
    char *mqttUser;
    char *mqttPassword;
};
#endif