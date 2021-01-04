#include "ArduinoMQTTMiddleware.h"

#include <PubSubClient.h>
#include "../../Helpers/ArduinoMQTTSerialization.h"
#include "../../../../WateringMachine/WateringMachine.h"

ArduinoMQTTMiddleware::ArduinoMQTTMiddleware(
    const char *mqttServer,
    int mqttPort,
    const char *mqttUser,
    const char *mqttPassword,
    WiFiClient *espc, const char *topicIn, const char *topicOut) : MiddlewareInterface(), wifiClient(espc), mqttServer(mqttServer), mqttPort(mqttPort), mqttUser(mqttUser), mqttPassword(mqttPassword), mqttTopicIn(topicIn), mqttTopicOut(topicOut)
{
    this->client = new PubSubClient(*espc);
}

bool ArduinoMQTTMiddleware::init(WateringMachine *wm)
{
    this->wateringMachine = wm;
    Serial.println("trying to connect to MQTT...");
    Serial.println(this->mqttServer);
    Serial.println(this->mqttPort);
    Serial.println(WiFi.localIP());

    if (!this->client->connected())
    {
        Serial.println("Connecting to MQTT...");

        if (!this->reconnect())
        {
            Serial.print("failed, rc=");
            Serial.print(client->state());
        }
    }
    return true;
}
bool ArduinoMQTTMiddleware::reconnect()
{
    this->client->setServer(this->mqttServer, this->mqttPort);
    this->client->setBufferSize(2048);
    //@see https://hobbytronics.com.pk/arduino-custom-library-and-pubsubclient-call-back/
    this->client->setCallback([this](char *topic, byte *payload, unsigned int length) { this->callback(topic, payload, length); });
    String clientId = "ArduinoMQTTClient";
    clientId += String(random(0xffff), HEX);
    Serial.println(clientId.c_str());
    //Serial.println(this->mqttUser);
    //Serial.println(this->mqttPassword);
    bool connected = false;

    if ((this->mqttUser != NULL) && (this->mqttUser[0] == '\0'))
    {
        connected = this->client->connect(clientId.c_str());
    }
    else
    {
        connected = this->client->connect(clientId.c_str(), this->mqttUser, this->mqttPassword);
    }
    if (connected)
    {
        Serial.println("connected");
        this->client->subscribe(this->mqttTopicIn);
    }
    return this->client->connected();
}
void ArduinoMQTTMiddleware::callback(char *topic, byte *payload, unsigned int length)
{

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.println(strstr(topic, "command") != NULL);
    Serial.println(length);
    Serial.print("Message:");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println("----");
    if (strstr(topic, "command") != NULL)
    {
        Serial.println("Command found");
        MQTTRequestResponse *mqtt_req = new MQTTRequestResponse();
        deserializeMQTT(mqtt_req, payload, length);
        Serial.println("Deserialized");
        Serial.print("Command: ");
        Serial.println(mqtt_req->command);
        if (strstr(mqtt_req->command, "configUpdate") != NULL)
        {
            if (this->wateringMachine->setConfig(mqtt_req->config))
            {
                Serial.print("Config has been updated");
            }
        }
        else if (strstr(mqtt_req->command, "turnWatering") != NULL)
        {
            this->wateringMachine->turnWatering();
        }
        else if (strstr(mqtt_req->command, "turnIdle") != NULL)
        {
            this->wateringMachine->turnIdle();
        }
        else if (strstr(mqtt_req->command, "turnLight") != NULL)
        {
            this->wateringMachine->turnLight();
        }
        else if (strstr(mqtt_req->command, "getStats") != NULL)
        {
            this->publishStats();
        }
        delete mqtt_req->config;
        delete mqtt_req->resources;
        delete mqtt_req->stats;
        delete mqtt_req->command;
        delete mqtt_req->event;
        delete mqtt_req->timestamp;
        delete mqtt_req;
        //delete ->
    }
    Serial.println();
    Serial.println("-----------------------");
};
bool ArduinoMQTTMiddleware::tick()
{

    if (!this->client->connected())
    {
        Serial.println("MQTT not connected. Reconnecting.");
        if (!this->reconnect())
        {
            Serial.print("failed, rc=");
            Serial.println(client->state());
        }
        return true;
    }
    else
    {
        Serial.println(".");
    }
    this->client->loop();
    return true;
};

void ArduinoMQTTMiddleware::setInfo(MQTTRequestResponse *mqtt_req){

};
bool ArduinoMQTTMiddleware::publishStats()
{
    if (!this->client->connected())
        return false;
    MQTTRequestResponse *mqtt_req = new MQTTRequestResponse();
    char event[] = "stats";
    char command[] = "";
    mqtt_req->event = event;
    mqtt_req->command = command;
    mqtt_req->config = this->wateringMachine->config;
    mqtt_req->resources = new WateringMachineResources(ESP.getFreeHeap());
    mqtt_req->stats = this->wateringMachine->getStats();
    //Serial.println("serializeMQTT");
    std::string json = serializeMQTT(mqtt_req);
    //Serial.println(this->mqttTopicOut);
    //char str[json.length() + 1];
    //strcpy(str, json.c_str());
    this->client->publish(this->mqttTopicOut, (char *)json.c_str());
    Serial.println("Sending stats");
    Serial.println(json.c_str());
    //delete mqtt_req->config;
    delete mqtt_req->resources;
    //delete mqtt_req->stats;
    delete[] mqtt_req->command;
    delete[] mqtt_req->event;
    //delete[] mqtt_req->timestamp;
    delete mqtt_req;
    return true;
}
bool ArduinoMQTTMiddleware::stateChange(WateringMachineStateBase *oldState, WateringMachineStateBase *nextState)
{
    if (!this->client->connected())
        return false;
    //this->client->publish("topicOut", "-------ArduinoMQTTMiddleware:statechange-");
    //Serial.println("-------ArduinoMQTTMiddleware:statechange-");
    MQTTRequestResponse *mqtt_req = new MQTTRequestResponse();
    char event[] = "stateChange";
    char command[] = "";
    mqtt_req->event = event;
    mqtt_req->command = command;
    mqtt_req->config = this->wateringMachine->config;
    mqtt_req->resources = new WateringMachineResources(ESP.getFreeHeap());
    mqtt_req->stats = this->wateringMachine->getStats();
    //Serial.println("serializeMQTT");
    std::string json = serializeMQTT(mqtt_req);
    //Serial.println(this->mqttTopicOut);
    //char str[json.length() + 1];
    //strcpy(str, json.c_str());
    this->client->publish(this->mqttTopicOut, (char *)json.c_str());
    Serial.println("State has changed");
    Serial.println(json.c_str());
    //delete mqtt_req->config; we dont have to we always copy values there (sic!)
    delete mqtt_req->resources;
    ///delete mqtt_req->stats;

    //not sure why i cannot delete those... isnt it a memory leak?
    //delete[] mqtt_req->event;
    //delete[] mqtt_req->command;
    //delete[] mqtt_req->timestamp;
    delete mqtt_req;

    return true;
};