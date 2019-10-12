#ifndef INTERRUPTSENSOR_H
#define INTERRUPTSENSOR_H

#include <Arduino.h>
#include "InterruptSensor.h"
#include "AtomicBuffer.h"

class InterruptSensor  
{

    public:
        InterruptSensor(const int pin, char identifier, void (*f)());
        void ReadSensor();
        bool IsFull();
        void PrintSensor();
        void WriteSensorToSD(String fileName);
        void ClearSensor();

    private:
        int _pin;
        AtomicBuffer _buffer;
};

#endif
