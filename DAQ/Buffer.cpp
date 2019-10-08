#include "Buffer.h"


// Constructor for the buffer.
// Requires the maximum number of bytes we want to store in the buffer.
Buffer::Buffer(int size)
{
    _dataBuf = new int[size * sizeof(int)];
    _timeBuf = new unsigned long[size * sizeof(unsigned long)];
    _headIndex = 0;
    _maxSize = size;
}

// Returns the number of items in the buffer.
int Buffer::GetSize()
{
    return(_headIndex);
}

// Appends a value to the end of the buffer.
// Doesn't append the value if the buffer is full.
void Buffer::Append(int value, unsigned long timestamp)
{
    if(_headIndex < _maxSize)
    {
        _dataBuf[_headIndex] = value;
        _timeBuf[_headIndex] = timestamp;
        _headIndex+=1;
    }
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

// 
void Buffer::ClearBuffer()
{
    _headIndex = 0;
}
