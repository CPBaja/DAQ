#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "Sensor.h"
#include "Buffer.h"

class Sensor  
{

    public:
        Sensor(const int pin, unsigned long microTimeInterval);
        bool ReadyToRead();
        void ReadSensor();
        int GetLastReading();
        int GetPin();
        bool IsFull();
        void PrintSensor();
        void WriteSensorToSD(File * file);
        void ClearSensor();
     
    private:
        unsigned long _lastTimestamp;
        unsigned long _microTimeInterval;
        int _pin;
        Buffer _buffer;
};

#endif
