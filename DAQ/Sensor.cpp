#include <Arduino.h>
#include <SD.h>

#include "Sensor.h"
#include "Buffer.h"

Sensor::Sensor(const int pin, unsigned long microTimeInterval)
{
    _pin = pin;
    _buffer.SetIdentifier(char(pin));
    _microTimeInterval = microTimeInterval;
}

bool Sensor::ReadyToRead()
{
    return(micros() - _lastTimestamp > _microTimeInterval);
}

void Sensor::ReadSensor()
{
    int reading = analogRead(_pin);
    _lastTimestamp = micros();
    _buffer.Append(reading);
}

int Sensor::GetLastReading()
{
    return(_buffer.GetLastValue());
}

int Sensor::GetPin()
{
    return(_pin);
}

bool Sensor::IsFull()
{
    return(_buffer.GetSize() == _buffer.GetMaxSize());
}

void Sensor::PrintSensor()
{
    _buffer.PrintBuffer();
}

void Sensor::WriteSensorToSD(File * file)
{
    _buffer.WriteBufferToSD(file);
}

void Sensor::ClearSensor()
{
    _buffer.ClearBuffer();
}
