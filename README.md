# Watering Machine

Modular Watering Machine (Arduino compatible) which allows you to water your crops/plants when needed and provide grow lights on specified interval.

## Introduction

It's an automatic plant watering system or smart irrigation system.

Main functionalities:

- monitors soil moisture with multiple moisture sensors
- waters the plants on specified intervals
- waters plants when soil moisture gets below certain treshold
- turns on grow lights on specified intervals and with specified duration
- allows you to configure and adjust moisture/watering/lighting duration/tresholds

Library aims to be platform agnostic (can be run on Arduino compatible devices: Arduino, ESP32, ESP8266, etc)

Interface with physical layer is separated from Watering Machine "business" logic.
Functions responsible for interfacing with physical infrastructure are injected into components upon their creation.

### States

Watering Machine
Change of states can be triggered with WateringMachine's commands:
![Green Wall in your appartment](./docs/images/uml/state_diagram_commands.png)
or when certain conditions are met:
![Green Wall in your appartment](./docs/images/uml/state_diagram_events.png)

Note: Lighting and Watering states are separate and cannot occur in parallel.

## Usage guide

### Configuration

Watering Machine behaviour can be cotnroller with the WateringMachineConfig object.
All times are in milliseconds.

Example Arduino code:

```cpp
WateringMachineConfig config;
setup(){
    const unsigned long ONE_HOUR = 1000 * 60 * 60; // hour constant

    config.LIGHTING_DURATION = ONE_HOUR * 8; // How long lighting session should last
    config.LIGHTING_INTERVAL = ONE_HOUR * 16; // Interval between lighting sessions
    config.WATERING_MAX_DURATION = ONE_HOUR /2; // How long watering should last
    config.WATERING_MAX_INTERVAL = ONE_HOUR * 24 * 7; // Maximal interval between waterings. After that time, watering will start even if avarage moisture level from sensors is over the MOISTURE_TRESHOLD
    config.WATERING_MIN_INTERVAL = ONE_HOUR; // Minimal interval between waterings. After watering is done it won't start again, before WATERING_MIN_INTERVAL has passed,even if avarage moisture level from sensors is below the MOISTURE_TRESHOLD
    config.MOISTURE_TRESHOLD = 52; //if avarage moisture level from sensors is below the MOISTURE_TRESHOLD watering starts
    config.WATERING_STOP_TRESHOLD = 80; //watering will stop if avarage moisture level from sensors reaches that value
}
```

### Sensors adjustment

1. Set DebugLevel to Debug: cLogSetDebugLevel(DebugLevel::DEBUG)
2. Run your Watering Machine
3. Check raw value for sensors when put into Water or wet ground, adjust sensorWetRawValue for sensor in ControlFunctions file
4. Check raw value for sensors when hold in Air or put into dry ground, adjust sensorDryRawValue for sensor in ControlFunctions file

### Arduino

### Example code

```cpp

// include components
#include "src/WateringMachine/Components/PulsePump.h"
#include "src/WateringMachine/Components/Light.h"
#include "src/WateringMachine/Components/MoistureSensor.h"
// include State factory (class geenrating states of Watering Machine)
#include "src/WateringMachine/States/StateFactory.h"
// include config class
#include "src/WateringMachine/WateringMachineConfig.h"
// include Watering Machine
#include "src/WateringMachine/WateringMachine.h"
// include Control Functions used to interface with hardware. Those are injected into Components' constructors.
#include "src/Firmware/Arduino/ControlFunctions.v1.h"

// config object instantiated
WateringMachineConfig config;
// pointer to WateringMachine
WateringMachine *wateringMachine;
// create pump object
static PulsePump pump(startPumpFunc, stopPumpFunc, initPumpFunc); //static so they wont be deleted after setup is detroyed
// create light object
static Light light(lightOnFunc, lightOffFunc, lightInitFunc);
/**
 * Arduno setup function
 */
void setup()
{
    // initialize the serial communication:
    Serial.begin(115200);
    const unsigned long ONE_HOUR = 1000 * 60 * 60; // hour constant

    config.LIGHTING_DURATION = ONE_HOUR * 8;          // How long lighting session should last
    config.LIGHTING_INTERVAL = ONE_HOUR * 16;         // Interval between lighting sessions
    config.WATERING_MAX_DURATION = ONE_HOUR / 2;      // How long watering should last
    config.WATERING_MAX_INTERVAL = ONE_HOUR * 24 * 7; // Maximal interval between waterings. After that time, watering will start even if avarage moisture level from sensors is over the MOISTURE_TRESHOLD
    config.WATERING_MIN_INTERVAL = ONE_HOUR;          // Minimal interval between waterings. After watering is done it won't start again, before WATERING_MIN_INTERVAL has passed,even if avarage moisture level from sensors is below the MOISTURE_TRESHOLD
    config.MOISTURE_TRESHOLD = 52;                    //if avarage moisture level from sensors is below the MOISTURE_TRESHOLD watering starts
    config.WATERING_STOP_TRESHOLD = 80;               //watering will stop if avarage moisture level from sensors reaches that value
    // Create sensor objects and add them to a vector
    static std::vector<MoistureSensor> sensors;
    sensors.push_back(MoistureSensor(Sensor1ReadFunc, sensorInitFunc));
    sensors.push_back(MoistureSensor(Sensor2ReadFunc, sensorInitFunc));
    // initialize StafeFactory object
    static StateFactory sf;
    //create a WateringMachine object
    wateringMachine = new WateringMachine(config, sf, light, pump, sensors);
    //init the WateringMachine
    wateringMachine->init();
};
/**
 * Arduino loop function
 */
void loop()
{
    // call tick function every time to handle WateringMachine logic
    wateringMachine->tick();
    // delay 5s
    delay(5000);
};

```

#### Example Schematic and Bill of Material

##### ESP8266

- [ESP8266 Bill of Material with links](./docs/bom/ESP82666_bom.md)

**Schematic:**
![ESP8266](./docs/images/schematics/WateringMachine_ESP8266_bb.png)

#### Test/Evaluate/Understand the code

1. Clone or download this repository
2. Uncomment the line // #define WATERING_TEST 1 in watering-machine.ino
3. Open watering-machine.ino inArduino IDE
4. Connect Arduino compatible device to USB port
5. Set port to correct value
6. Click Upload
7. After upload has finished open Serial Terminal and set baud rate to 115200
8. You can see now logs printed by Watering Machine
9. You can experiment with different values returned by Control function, reupload the code and see how this influences the behaviour

#### Run on your own device and setup

1. Build/prototype your Watering Machine (see example Schematic and Bill of Materials)
2. Clone or download this repository
3. Rename root folder e.g. my_watering_machine
4. Duplicate /watering-machine.ino and rename it to mywaterin_machine.ino
5. Copy /src/Firmware/Arduino/ControlFunctions.v[x].h to /libraries/Arduino/ControlFunctions.v[x].h folder
6. change include path of ControlFunctions.v[x].h to the new one
7. Adjust pin numbers in ControlFunctions file to match your build

## Use Cases

![Green Wall in your appartment](./docs/images/green_wall.jpg)

## Project structure

``` folder
.
├── docs - documentation and other file assets (images, uml etc)
├── libraries - Here you can place some aditional libraries if needed
├── src - Waterng Machine code
│   ├── Firmware - Control Functions which allow to communicate with a hardware/physical components. Those are injected to component objects upon their creation.
│   │   ├── Arduino - Arduino compatible examples of Control functions
│   │   └── ControlFunctions.Test.h - Test Control Functions to experiment with
│   └── WateringMachine/
│       ├── Components/ - concerte classes of the components (sensors, pump, lights etc.)
│       │   └── StateMachineInterfaces/ - Abstract Component state MAchine classes to be derived by concerte component classes.
│       ├── States/ - Watering MAchine State classes (Watering, Idle, Lighting)
│       ├── Utils/ - Utility classes (logs, formatting, etc. )
│       ├── WateringMachine.cpp
│       ├── WateringMachine.h - main control class of the Watering Machine
│       └── WateringMachineConfig.h 
└── watering-machine.ino - example Arduino sketch with fulll configuration
```

## Improvements and changes

## Questions

For questions about the usage of the libraries, please fill in an issue labeled "question" in Github as that makes it far easier to track them.

## Bugs and issues

For bugs in the libraries, please fill in an issue in Github as that makes it far easier to track them. If possible provide a minimal code snippet that exposes the bug. Also proposals for solutions are welcome.
Issues are not bugs but still possible problematic. E.g. if a library is too slow for your application that is an issue, not a bug. Please fill in an issue and provide as much details about your requirements.

## License and Warranty

Apache License
Version 2.0, January 2004
[http://www.apache.org/licenses/](http://www.apache.org/licenses/)

Please check the file LICENSE and NOTICE for the details.
Give credits a it's requried by the license and if you want to donate, please donate to charity like "doctors without borders".
