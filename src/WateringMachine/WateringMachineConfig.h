#ifndef WATERING_MACHINE_CONFIG_H
#define WATERING_MACHINE_CONFIG_H
struct WateringMachineConfig
{
  unsigned long LIGHTING_INTERVAL;
  unsigned long LIGHTING_DURATION;
  unsigned long WATERING_MAX_DURATION;
  unsigned long WATERING_MAX_INTERVAL;
  unsigned long WATERING_MIN_INTERVAL;
  unsigned long MOISTURE_TRESHOLD;
  unsigned long MOISTURE_MEASUREMENT_INTERVAL;
  unsigned long WATERING_STOP_TRESHOLD;
};
void loadWateringConfig(const char *file, WateringMachineConfig &config);
#endif