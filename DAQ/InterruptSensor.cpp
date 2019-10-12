#include <Arduino.h>
#include <SD.h>

#include "InterruptSensor.h"
#include "AtomicBuffer.h"

InterruptSensor::InterruptSensor(const int pin, char identifier, void (*f)())
{
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), f, CHANGE);
    _pin = pin;
    _buffer.SetIdentifier(identifier);
}

void InterruptSensor::ReadSensor()
{
    int reading = digitalRead(_pin);
    _buffer.Append(reading, micros());
}

bool InterruptSensor::IsFull()
{
    return(_buffer.GetSize() == _buffer.GetMaxSize());
}

void InterruptSensor::PrintSensor()
{
    _buffer.PrintBuffer();
}

void InterruptSensor::WriteSensorToSD(String fileName)
{
    _buffer.WriteBufferToSD(fileName);
}

void InterruptSensor::ClearSensor()
{
    _buffer.Swap();
    _buffer.ClearBuffer();
}
