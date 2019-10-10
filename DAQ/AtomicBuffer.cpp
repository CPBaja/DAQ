#include "AtomicBuffer.h"
#include "Buffer.h"

// Constructor for the atomic buffer, which is really just two buffers.
// Requires the maximum number of slots we want for the buffer.
AtomicBuffer::AtomicBuffer(int size, char identifier)
{
    _primaryBuffer = new Buffer(size, identifier);
    _secondaryBuffer = new Buffer(size, identifier);
    _currentBuffer = '0';
    _identifier = identifier;
}

// Appends a value to the end of the buffer.
// Doesn't append the value if the buffer is full.
int AtomicBuffer::Append(int value, unsigned long timestamp)
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer->Append(value, timestamp));
    }
    else
    {
        return(_secondaryBuffer->Append(value, timestamp));
    }
}

// Returns the value of an item at the index.
int AtomicBuffer::GetValue(int index)
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer->GetValue(index));
    }
    else
    {
        return(_secondaryBuffer->GetValue(index));
    }
}

// Returns the value of a time at the index.
unsigned long AtomicBuffer::GetTime(int index)
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer->GetTime(index));
    }
    else
    {
        return(_secondaryBuffer->GetTime(index));
    }
}

// Returns the number of items in the buffer.
int AtomicBuffer::GetSize()
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer->GetSize());
    }
    else
    {
        return(_secondaryBuffer->GetSize());
    }
}

// Clears the buffer that isn't the current buffer.
// Why? Because the _currentBuffer is the one we're always ready to write data to.
// When we clear the buffer, it's because we just wrote the data to SD.
// When we're writing data to SD, we don't want to add any more data into that buffer.
// Therefore, the current buffer is never written to the SD.
// So we never clear the current buffer.
void AtomicBuffer::ClearBuffer()
{
    if(_currentBuffer == '0')
    {
        return(_secondaryBuffer->ClearBuffer());
    }
    else
    {
        return(_primaryBuffer->ClearBuffer());
    }
}

void AtomicBuffer::Swap()
{
    if(_currentBuffer == '0')
    {
        _primaryBuffer->ClearBuffer();
        _currentBuffer = '1';
    }
    else
    {
        _secondaryBuffer->ClearBuffer();
        _currentBuffer = '0';
    }
}
