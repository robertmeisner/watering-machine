#ifndef WATERING_MACHINE_STATS_H
#define WATERING_MACHINE_STATS_H
#include <string>
struct WateringMachineStats
{
    WateringMachineStats() : averageMoisture(100),
                             waterLevel(100),
                             statePrevious(""),
                             state(""),
                             pumpOn(false),
                             lightOn(false),
                             pumpDurationSinceLastChange(0),
                             lightDurationSinceLastChange(0)
    {
        for (int i = 0; i < 10; i++)
        {
            this->moistureSensorActive[i] = false;
            this->moistureSensorReadings[i] = 0.0;
        }
    }
    bool moistureSensorActive[10];
    float moistureSensorReadings[10];
    float averageMoisture;
    float waterLevel;
    std::string statePrevious;
    std::string state;
    bool pumpOn;
    bool lightOn;
    unsigned long pumpDurationSinceLastChange;
    unsigned long lightDurationSinceLastChange;
};
#endif
