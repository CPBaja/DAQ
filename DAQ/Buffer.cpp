#include <Arduino.h>
#include <SD.h>

#include "Buffer.h"

// Constructor for the buffer.
Buffer::Buffer()
{
    _headIndex = 0;
}

void Buffer::SetIdentifier(char identifier)
{
    _identifier = identifier;
}

// Appends a value to the end of the buffer.
// Doesn't append the value if the buffer is full.
int Buffer::Append(int value)
{
    if(_headIndex < _maxSize)
    {
        _dataBuf[_headIndex] = value;
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
    Serial.print(int(_identifier));
    for(int index = 0;index < _maxSize;index++)
    {
        Serial.print(":");
        Serial.print(_dataBuf[index]);
    }
    Serial.print(":");
    Serial.println(micros());
}

void Buffer::WriteBufferToSD(File * file)
{    
    file->write(_identifier);
    
    for(int index = 0;index < _headIndex;index++)
    {
        file->write((byte*)&_dataBuf[index], sizeof(short int));
    }
    
    file->flush();
}

// 'Clears' the buffer. Really just resets the head index. Very fast.
// Slow implementation would be iterating through the buffer, and setting each value to null.
void Buffer::ClearBuffer()
{
    _headIndex = 0;
}
