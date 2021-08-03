#ifndef WATERING_MACHINE_CONFIG_H
#define WATERING_MACHINE_CONFIG_H
/*
 const unsigned long ONE_HOUR = 1000 * 60 * 60; // hour constant

    config.LIGHTING_DURATION = ONE_HOUR * 12;          // How long lighting session should last
    config.LIGHTING_INTERVAL = ONE_HOUR * 12;         // Interval between lighting sessions
    config.WATERING_MAX_DURATION = ONE_HOUR / 2;      // How long watering should last
    config.WATERING_MAX_INTERVAL = ONE_HOUR * 24 * 7; // Maximal interval between waterings. After that time, watering will start even if avarage moisture level from sensors is over the MOISTURE_TRESHOLD
    config.WATERING_MIN_INTERVAL = ONE_HOUR;          // Minimal interval between waterings. After watering is done it won't start again, before WATERING_MIN_INTERVAL has passed,even if avarage moisture level from sensors is below the MOISTURE_TRESHOLD
    config.MOISTURE_TRESHOLD = 50;                    //if avarage moisture level from sensors is below the MOISTURE_TRESHOLD watering starts
    config.WATERING_STOP_TRESHOLD = 90;               //watering will stop if avarage moisture level from sensors reaches that value
    */
const unsigned long ONE_HOUR = 1000 * 60 * 60; // hour constant
struct WateringMachineConfig
{
  WateringMachineConfig() : LIGHTING_INTERVAL(ONE_HOUR*12),
                            LIGHTING_DURATION(ONE_HOUR * 12),
                            WATERING_MAX_DURATION(ONE_HOUR / 6),
                            WATERING_MAX_INTERVAL(ONE_HOUR * 24 * 7),
                            WATERING_MIN_INTERVAL(ONE_HOUR),
                            MOISTURE_TRESHOLD(40),
                            MOISTURE_MEASUREMENT_INTERVAL(1000),
                            WATERING_STOP_TRESHOLD(90) {}
  unsigned long LIGHTING_INTERVAL;
  unsigned long LIGHTING_DURATION;
  unsigned long WATERING_MAX_DURATION;
  unsigned long WATERING_MAX_INTERVAL;
  unsigned long WATERING_MIN_INTERVAL;
  unsigned long MOISTURE_TRESHOLD;
  unsigned long MOISTURE_MEASUREMENT_INTERVAL;
  unsigned long WATERING_STOP_TRESHOLD;
};
#endif