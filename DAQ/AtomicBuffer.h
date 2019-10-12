#ifndef ATOMICBUFFER_H
#define ATOMICBUFFER_H

#include "Buffer.h"

class AtomicBuffer
{

    public:
        AtomicBuffer();
        void SetIdentifier(char identifier);
        int Append(int value, unsigned long timestamp);
        int GetValue(int index);
        unsigned long GetTime(int index);
        int GetSize();
        int GetMaxSize();
        void PrintBuffer();
        void WriteBufferToSD(String fileName);
        void ClearBuffer();
        void Swap();

    private:
        unsigned char _currentBuffer;
        Buffer _primaryBuffer;
        Buffer _secondaryBuffer;
};

#endif
