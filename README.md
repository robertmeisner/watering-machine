# Watering Machine

Modular Watering Machine (Arduino compatible)

## Introduction

This repository contains a working library

Allows you to:

- monitor soil moisture with multiple moisture sensors
- water the plants on specified intervals
- water plants when soil moisture gets below certain treshold
- turn on grow lights on specified intervals and with specified duration
- configure and adjust moisture/watering/lighting duration/tresholds

Library aims to be platform agnostic (can be run on Arduino compatible devices: Arduino, ESP32, ESP8266, etc)

Interface with physical layer is separated from Watering Machine "business" logic.
Functions responsible for interfacing with physical infrastructure are injected into components upon their creation.

## Installation guide

## Use Cases

![Green Wall in your appartment](./docs/images/green_wall.jpg)

## Improvements and changes

## Questions

For questions about the usage of the libraries, please fill in an issue labeled "question" in Github as that makes it far easier to track them.

## Bugs and issues

For bugs in the libraries, please fill in an issue in Github as that makes it far easier to track them. If possible provide a minimal code snippet that exposes the bug. Also proposals for solutions are welcome.
Issues are not bugs but still possible problematic. E.g. if a library is too slow for your application that is an issue, not a bug. Please fill in an issue and provide as much details about your requirements.

## License and Warranty

Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/

Please check the file LICENSE and NOTICE for the details.
Give credits a it's requried by the license and if you want to donate, please donate to charity like "doctors without borders".
