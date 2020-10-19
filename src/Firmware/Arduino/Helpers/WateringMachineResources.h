#ifndef WATERING_MACHINE_RESOURCES_H
#define WATERING_MACHINE_RESOURCES_H
#include <string>
struct WateringMachineResources
{
    WateringMachineResources() : freeRAM(0)
    {
    }
    WateringMachineResources(long ram) : freeRAM(ram)
    {
    }
    long freeRAM;
};
#endif