#include <Arduino.h>
#include <SD.h>

#include "Sensor.h"
#include "Buffer.h"

Sensor::Sensor(const int pin, char identifier)
{
    _buffer.SetIdentifier(identifier);
    _pin = pin;
}

void Sensor::ReadSensor()
{
    int reading = analogRead(_pin);
    _buffer.Append(reading, micros());
}

void Sensor::PrintSensor()
{
    _buffer.PrintBuffer();
}

void Sensor::WriteSensorToSD(File file, String fileName)
{
    _buffer.WriteBufferToSD(file, fileName);
}
