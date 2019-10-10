#include "AtomicBuffer.h"
#include "Buffer.h"

// Constructor for the atomic buffer, which is really just two buffers.
// Requires the maximum number of slots we want for the buffer.
AtomicBuffer::AtomicBuffer()
{
    _currentBuffer = '0';
}

void AtomicBuffer::SetIdentifier(char identifier)
{
    _primaryBuffer.SetIdentifier(identifier);
    _secondaryBuffer.SetIdentifier(identifier);
}

// Appends a value to the end of the buffer.
// Doesn't append the value if the buffer is full.
int AtomicBuffer::Append(int value, unsigned long timestamp)
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer.Append(value, timestamp));
    }
    else
    {
        return(_secondaryBuffer.Append(value, timestamp));
    }
}

// Returns the value of an item at the index.
int AtomicBuffer::GetValue(int index)
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer.GetValue(index));
    }
    else
    {
        return(_secondaryBuffer.GetValue(index));
    }
}

// Returns the value of a time at the index.
unsigned long AtomicBuffer::GetTime(int index)
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer.GetTime(index));
    }
    else
    {
        return(_secondaryBuffer.GetTime(index));
    }
}

// Returns the number of items in the buffer.
int AtomicBuffer::GetSize()
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer.GetSize());
    }
    else
    {
        return(_secondaryBuffer.GetSize());
    }
}

// Swaps the current buffer and prints the previous current buffer.
void AtomicBuffer::PrintBuffer()
{
    Swap();

    if(_currentBuffer == '0')
    {
        return(_secondaryBuffer.PrintBuffer());
    }
    else
    {
        return(_primaryBuffer.PrintBuffer());
    }
}

void AtomicBuffer::WriteBufferToSD(File file, String fileName)
{
    Swap();

    if(_currentBuffer == '0')
    {
        return(_secondaryBuffer.WriteBufferToSD(file, fileName));
    }
    else
    {
        return(_primaryBuffer.WriteBufferToSD(file, fileName));
    }
}

// Clears the current buffer.
void AtomicBuffer::ClearBuffer()
{
    if(_currentBuffer == '0')
    {
        return(_primaryBuffer.ClearBuffer());
    }
    else
    {
        return(_secondaryBuffer.ClearBuffer());
    }
}

// Swaps the current buffer.
void AtomicBuffer::Swap()
{
    if(_currentBuffer == '0')
    {
        _currentBuffer = '1';
    }
    else
    {
        _currentBuffer = '0';
    }
}
