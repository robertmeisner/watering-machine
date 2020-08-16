#include "MQTTMiddleware.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
void callback(char *topic, byte *payload, unsigned int length)
{

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println();
    Serial.println("-----------------------");
}
MQTTMiddleware::MQTTMiddleware(
                               char *mqttServer,
                               int mqttPort,
                               char *mqttUser,
                               char *mqttPassword,
                               WiFiClient &espc) : MiddlewareInterface(),wifiClient(espc),client(PubSubClient(espc))
{
}

bool MQTTMiddleware::init()
{
    this->client.setServer(this->mqttServer, this->mqttPort);
    //@see https://hobbytronics.com.pk/arduino-custom-library-and-pubsubclient-call-back/
    this->client.setCallback([this] (char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });
    while (!this->client.connected())
    {
        Serial.println("Connecting to MQTT...");

        if (this->client.connect("ESP8266Client", mqttUser, mqttPassword))
        {

            Serial.println("connected");
        }
        else
        {

            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void MQTTMiddleware::callback(char *topic, byte *payload, unsigned int length)
{

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println();
    Serial.println("-----------------------");
};
bool MQTTMiddleware::tick()
{
    this->client.loop();
};

bool MQTTMiddleware::stateChange(StateType nextState){
    
}