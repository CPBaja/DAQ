#include <Arduino.h>
#include "Buffer.h"

// Constructor for the buffer.
// Requires the maximum number of slots we want for the buffer.
Buffer::Buffer(char identifier)
{
    //_dataBuf = new int[size * sizeof(int)];
    //_timeBuf = new unsigned long[size * sizeof(unsigned long)];
    _headIndex = 0;
    //_maxSize = size;
    _identifier = identifier;
}

// Appends a value to the end of the buffer.
// Doesn't append the value if the buffer is full.
int Buffer::Append(int value, unsigned long timestamp)
{
    if(_headIndex < _maxSize)
    {
        _dataBuf[_headIndex] = value;
        _timeBuf[_headIndex] = timestamp;
        _headIndex+=1;
    }
    return(_maxSize - _headIndex);
}

// Returns the value of an item at the index.
int Buffer::GetValue(int index)
{
    return(_dataBuf[index]);
}

// Returns the value of a time at the index.
unsigned long Buffer::GetTime(int index)
{
    return(_timeBuf[index]);
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
    for(int index = 0;index < _maxSize;index++)
    {
        Serial.print(_dataBuf[index]);
        Serial.print(":");
        Serial.print(_timeBuf[index]);
        Serial.print(":");
    }
    Serial.println();
}

// 'Clears' the buffer. Really just resets the head index. Very fast.
// Slow implementation would be iterating through the buffer, and setting each value to null.
void Buffer::ClearBuffer()
{
    _headIndex = 0;
}
