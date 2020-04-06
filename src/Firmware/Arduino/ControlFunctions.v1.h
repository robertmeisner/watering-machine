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
static int upperLimit = 23000;
static int lowerLimit = 8400;
#define MOISTURE_SENSOR_SAMPLES 5
#define ADS_GAIN GAIN_ONE              // change to GAIN_TWOTHIRDS if using 5V!!!!
#define ADS_SCALE_FACTOR 0.125f / 1000 // adjust scale factor to ADS_GAIN
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
    adc = constrain(adc, lowerLimit, upperLimit); // Keep the ranges!
    adc = map(adc, lowerLimit, upperLimit, 100, 0);
    return adc;
}

float Sensor1ReadFunc()
{
    return _readAds(0, "Sensor #1");
}
float Sensor2ReadFunc()
{
    return _readAds(1, "Sensor #2");
}

bool startPumpFunc()
{
    digitalWrite(14, LOW);
    return true;
}
bool stopPumpFunc()
{
    digitalWrite(14, HIGH);
    return true;
}
bool initPumpFunc()
{
    pinMode(14, OUTPUT);
    stopPumpFunc();
    return true;
}

bool lightOnFunc()
{
    digitalWrite(13, LOW);
    return true;
}
bool lightOffFunc()
{
    digitalWrite(13, HIGH);
    return true;
}
bool lightInitFunc()
{
    pinMode(13, OUTPUT);
    lightOffFunc();
    return true;
}
#endif