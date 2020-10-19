#ifndef ArduinoFunctionsTest_h
#define ArduinoFunctionsTest_h
unsigned long timeFunctionValue = 100000;
unsigned long timeFunction() {
    return timeFunctionValue;
}
bool sensorInitFunc()
{
    return true;
}
float Sensor1ReadFuncValue = 10;
float Sensor1ReadFunc()
{
    return Sensor1ReadFuncValue;
}
float Sensor2ReadFuncValue = 50;
float Sensor2ReadFunc()
{
    return Sensor2ReadFuncValue;
}
bool initPumpFunc()
{
    return true;
}
bool startPumpFunc()
{
    return true;
}
bool stopPumpFunc()
{
    return true;
}

bool lightOnFunc()
{
    return true;
}
bool lightOffFunc()
{
    return true;
}
bool lightInitFunc()
{
    return true;
}
#endif