#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Sensor.h"
#include "Buffer.h"

class Sensor  
{

    public:
        Sensor(const int pin, char identifier, unsigned long microTimeInterval);
        bool ReadyToRead();
        void ReadSensor();
        bool IsFull();
        void PrintSensor();
        void WriteSensorToSD(String fileName);
        void ClearSensor();
     
    private:
        unsigned long _lastTimestamp;
        unsigned long _microTimeInterval;
        int _pin;
        Buffer _buffer;
};

#endif
