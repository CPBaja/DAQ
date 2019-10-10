#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class Sensor  
{

    public:
        Sensor(const int pin, char identifier);
        void ReadSensor();
        void PrintSensor();
        void WriteSensorToSD();
     
    private:
        const int _pin;
        Buffer * _buffer;
};

#endif
