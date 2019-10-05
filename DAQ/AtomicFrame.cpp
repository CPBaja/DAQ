#include "AtomicFrame.h"
#include "Buffer.h"

// Constructor for the atomic frame.
// Requires the maximum number of bytes we want to store in the frame.
AtomicFrame::AtomicFrame(){}

void AtomicFrame::AppendToBuffer(char name, int value, unsigned long timestamp)
{
    unsigned index = unsigned(name);
    if(_bufPtrs[index] != 0)
    {
        _bufPtrs[index] = new Buffer();
    }
    
    _bufPtrs[index]->Append(value, timestamp);    
}

bool AtomicFrame::ReadyToStore()
{
    int currentFrameSize = 0;
    
    for(int i = 0;i < 256;i++)
    {
        if(_bufPtrs[i] != 0)
        {
            currentFrameSize += _bufPtrs[i]->_headIndex;
        }
    }
    
    return(currentFrameSize >= MAX_BUFFER_SIZE);
}

void AtomicFrame::ClearBuffers()
{
    for(int i = 0;i < 256;i++)
    {
        if(_bufPtrs[i] != 0)
        {
            _bufPtrs[i]->ClearBuffer();
        }
    }
}
