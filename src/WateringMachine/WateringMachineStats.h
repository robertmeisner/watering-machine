#ifndef WATERING_MACHINE_STATS_H
#define WATERING_MACHINE_STATS_H
#include <string>
struct WateringMachineStats
{
    WateringMachineStats() : averageMoisture(100),
                             stateName("undefined"),
                             wateringOn(false),
                             lightOn(false)
    {
    }
    bool moistureSensorActive[10];
    float moistureSensorReadings[10];
    float averageMoisture;
    bool wateringOn;
    bool lightOn;
    std::string stateName;
};
#endif
