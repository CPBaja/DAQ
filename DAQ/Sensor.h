#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Sensor.h"
#include "Buffer.h"

class Sensor  
{

    public:
        Sensor(const int pin, char identifier);
        void ReadSensor();
        void PrintSensor();
        void WriteSensorToSD(File file, String fileName);
     
    private:
        int _pin;
        Buffer _buffer;
};

#endif
