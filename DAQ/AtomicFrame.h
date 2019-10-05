#ifndef ATOMICFRAME_H
#define ATOMICFRAME_H

#include "Buffer.h"

class AtomicFrame
{

    public:
        AtomicFrame();
        void AppendToBuffer(char name, int value, unsigned long timestamp);
        bool ReadyToStore();
        void ClearBuffers();

    private:
        Buffer *_bufPtrs[256];
};

#endif