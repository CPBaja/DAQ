#include <Arduino.h>
#include <SD.h>

#include "Sensor.h"
#include "Buffer.h"

Sensor::Sensor(const int pin, char identifier, unsigned long microTimeInterval)
{
    _pin = pin;
    _buffer.SetIdentifier(identifier);
    _microTimeInterval = microTimeInterval;
}

bool Sensor::ReadyToRead()
{
    return(abs(micros() - _lastTimestamp) > _microTimeInterval);
}

void Sensor::ReadSensor()
{
    int reading = analogRead(_pin);
    _lastTimestamp = micros();
    _buffer.Append(reading, _lastTimestamp);
}

bool Sensor::IsFull()
{
    return(_buffer.GetSize() == _buffer.GetMaxSize());
}

void Sensor::PrintSensor()
{
    _buffer.PrintBuffer();
}

void Sensor::WriteSensorToSD(File file, String fileName)
{
    _buffer.WriteBufferToSD(file, fileName);
}

void Sensor::ClearSensor()
{
    _buffer.ClearBuffer();
}
