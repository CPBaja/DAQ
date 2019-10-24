#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"

// Constructor for the buffer.
Buffer::Buffer()
{
    _initialTime = 0;
    _headIndex = 0;
}

void Buffer::SetIdentifier(char identifier)
{
    _identifier = identifier;
}

// Appends a value to the end of the buffer.
// Doesn't append the value if the buffer is full.
int Buffer::Append(int value, unsigned long timestamp)
{
    if(_headIndex < _maxSize)
    {
        _dataBuf[_headIndex] = value;
        if(_initialTime == 0)
        {
            _initialTime = timestamp;
        }
        _headIndex+=1;
    }
    return(_maxSize - _headIndex);
}

// Returns the value of an item at the index.
int Buffer::GetValue(int index)
{
    return(_dataBuf[index]);
}

// Returns the number of items in the buffer.
int Buffer::GetSize()
{
    return(_headIndex);
}

int Buffer::GetMaxSize()
{
    return(_maxSize);
}

void Buffer::PrintBuffer()
{
    Serial.print(_identifier);
    Serial.print(":");
    Serial.print(_initialTime);
    for(int index = 0;index < _maxSize;index++)
    {
        Serial.print(":");
        Serial.print(_dataBuf[index]);
    }
    Serial.print(":");
    Serial.println(micros());
}

void Buffer::WriteBufferToSD(String fileName)
{
    char __dataFileName[sizeof(fileName)];
    fileName.toCharArray(__dataFileName, sizeof(__dataFileName));
    File file = SD.open(__dataFileName, FILE_WRITE);
    
    file.write(_identifier);
    file.write((byte*)&_initialTime, sizeof(unsigned long));
    
    for(int index = 0;index < _headIndex;index++)
    {
        file.write((byte*)&_dataBuf[index], sizeof(int));
    }
    unsigned long curTime = micros();
    file.write((byte*)&curTime, sizeof(unsigned long));
    
    file.flush();
    file.close();
}

// 'Clears' the buffer. Really just resets the head index and timestamp. Very fast.
// Slow implementation would be iterating through the buffer, and setting each value to null.
void Buffer::ClearBuffer()
{
    _initialTime = 0;
    _headIndex = 0;
}
