#include "Buffer.h"


// Constructor for the buffer.
// Requires the maximum number of bytes we want to store in the buffer.
Buffer::Buffer()
{
    _headIndex = 0;
}

int Buffer::GetSizeInBytes()
{
    return(_headIndex);
}

// Appends a value to the end of the buffer.
void Buffer::Append(int value, unsigned long timestamp)
{
    if(_headIndex < MAX_BUFFER_SIZE)
    {
        _dataBuf[_headIndex] = value;
        _timeBuf[_headIndex] = timestamp;
        _headIndex+=1;
    }

}

int Buffer::GetValue(int index)
{
    return(_dataBuf[index]);
}

unsigned long Buffer::GetTime(int index)
{
    return(_timeBuf[index]);
}

void Buffer::ClearBuffer()
{
    _headIndex = 0;
}
