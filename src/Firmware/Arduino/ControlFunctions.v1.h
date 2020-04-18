#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#ifndef ArduinoFunctions_h
#define ArduinoFunctions_h
// The ADC input range (or gain) can be changed via the following
// functions, but be careful never to exceed VDD +0.3V max, or to
// exceed the upper and lower limits if you adjust the input range!
// Setting these values incorrectly may destroy your ADC!
//                                                                ADS1015  ADS1115
//                                                                -------  -------
// ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
// ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
// ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
// ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
// ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
// ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

//ads.begin(1,0);                // for ESP8266  SDA, SCL can be specified
static Adafruit_ADS1115 ads;
static bool sensorsInitiated = false;
static int sensorRawDryValue1 = 27000;
static int sensorRawWetValue1 = 10300;
static int sensorRawDryValue2 = 27300;
static int sensorRawWetValue2 = 10500;
#define MOISTURE_SENSOR_SAMPLES 5
#define ADS_GAIN GAIN_ONE              // change to GAIN_TWOTHIRDS if using 5V!!!!
#define ADS_SCALE_FACTOR 0.125f / 1000 // adjust scale factor to ADS_GAIN

#define PUMP_PIN 14
#define LIGHTS_PIN 13
#define SENSOR1_PIN 0
#define SENSOR2_PIN 1

bool sensorInitFunc()
{
    if (!sensorsInitiated)
    {
        ads.setGain(GAIN_ONE);
        ads.begin();
        sensorsInitiated = true;
    }
    return true;
}
float _readAds(int pin, String sensorName = "")
{
    float adc = 0;
    int sample_count = 0;
    //additional smoothing
    for (int i = 0; i <= MOISTURE_SENSOR_SAMPLES; i++)
    {
        adc += ads.readADC_SingleEnded(pin);
        delay(50);
    }
    adc = adc / MOISTURE_SENSOR_SAMPLES;
    Serial.println("Moisture Sensor| " + sensorName + " Raw Value: " + String(adc));
    float volts = adc * ADS_SCALE_FACTOR;
    Serial.println("Moisture Sensor| " + sensorName + " Volts Value: " + String(volts));
    if (sensorName=="Sensor #1")
    {
        adc = constrain(adc, sensorRawWetValue1, sensorRawDryValue1); // Keep the ranges!
        adc = map(adc, sensorRawWetValue1, sensorRawDryValue1, 100, 0);
    }
    else
    {
        adc = constrain(adc, sensorRawWetValue2, sensorRawDryValue2); // Keep the ranges!
        adc = map(adc, sensorRawWetValue2, sensorRawDryValue2, 100, 0);
    }
    return adc;
}

float Sensor1ReadFunc()
{
    return _readAds(SENSOR1_PIN, "Sensor #1");
}
float Sensor2ReadFunc()
{
    return _readAds(SENSOR2_PIN, "Sensor #2");
}

bool startPumpFunc()
{
    digitalWrite(PUMP_PIN, LOW);
    return true;
}
bool stopPumpFunc()
{
    digitalWrite(PUMP_PIN, HIGH);
    return true;
}
bool initPumpFunc()
{
    pinMode(PUMP_PIN, OUTPUT);
    stopPumpFunc();
    return true;
}

bool lightOnFunc()
{
    digitalWrite(LIGHTS_PIN, LOW);
    return true;
}
bool lightOffFunc()
{
    digitalWrite(LIGHTS_PIN, HIGH);
    return true;
}
bool lightInitFunc()
{
    pinMode(LIGHTS_PIN, OUTPUT);
    lightOffFunc();
    return true;
}
#endif