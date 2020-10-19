#include "ArduinoMQTTMiddleware.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "../../Helpers/MemoryFree/MemoryFree.h"
#include "../../Helpers/ArduinoMQTTSerialization.h"
#include "../../../../WateringMachine/WateringMachine.h"

ArduinoMQTTMiddleware::ArduinoMQTTMiddleware(
    char *mqttServer,
    int mqttPort,
    char *mqttUser,
    char *mqttPassword,
    WiFiClient *espc, char *topicIn, char *topicOut) : MiddlewareInterface(), wifiClient(espc), mqttServer(mqttServer), mqttPort(mqttPort), mqttUser(mqttUser), mqttPassword(mqttPassword), mqttTopicIn(topicIn), mqttTopicOut(topicOut)
{
    this->client = new PubSubClient(*espc);
}

bool ArduinoMQTTMiddleware::init(WateringMachine *wm)
{
    this->wateringMachine = wm;
    Serial.println("trying to connect to MQTT...");
    this->client->setServer(this->mqttServer, this->mqttPort);
    this->client->setBufferSize(2048);
    //@see https://hobbytronics.com.pk/arduino-custom-library-and-pubsubclient-call-back/
    this->client->setCallback([this](char *topic, byte *payload, unsigned int length) { this->callback(topic, payload, length); });
    while (!this->client->connected())
    {
        Serial.println("Connecting to MQTT...");
        String clientId = "ArduinoMQTTMiddleware-";
        clientId += String(random(0xffff), HEX);
        if (this->client->connect(clientId.c_str(), this->mqttUser, this->mqttPassword))
        {

            Serial.println("connected");
            this->client->subscribe(this->mqttTopicIn);
        }
        else
        {

            Serial.print("failed, rc=");
            Serial.print(client->state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void ArduinoMQTTMiddleware::callback(char *topic, byte *payload, unsigned int length)
{

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    if (strstr(topic, "/command") != NULL)
    {

        MQTTRequestResponse *req = deserializeMQTT(payload, length);
        if (strstr(req->command.c_str(), "configUpdate") != NULL)
        {
            if (this->wateringMachine->setConfig(req->config))
            {
                Serial.print("Config has been updated");
            }
        }
    }
    Serial.println();
    Serial.println("-----------------------");
};
bool ArduinoMQTTMiddleware::tick()
{

    Serial.println("-------ArduinoMQTTMiddleware:tick-");

    this->client->loop();
};

bool ArduinoMQTTMiddleware::stateChange(WateringMachineStateBase *oldState, WateringMachineStateBase *nextState)
{
    //this->client->publish("topicOut", "-------ArduinoMQTTMiddleware:statechange-");
    //Serial.println("-------ArduinoMQTTMiddleware:statechange-");
    MQTTRequestResponse *mqtt_req = new MQTTRequestResponse();
    mqtt_req->event = "stateChange";
    mqtt_req->config = this->wateringMachine->config;
    mqtt_req->resources = new WateringMachineResources(freeMemory());
    //mqtt_req->resources->freeRAM = freeMemory();
    //Serial.println("serializeMQTT");
    std::string json = serializeMQTT(mqtt_req);
    //Serial.println(this->mqttTopicOut);
    //char str[json.length() + 1];
    //strcpy(str, json.c_str());
    this->client->publish(this->mqttTopicOut, (char *)json.c_str());
    Serial.println("State has changed");
    Serial.println(json.c_str());
    delete mqtt_req;
    return true;
}
