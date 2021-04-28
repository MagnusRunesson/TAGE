#include "mem.h"

const unsigned int MEMAREA_HEADER_SIZE = 4;
const unsigned int MEMAREA_BITMASK_SIZE = 0x000fffff;

const unsigned int MEMCHUNK_HEADER_SIZE = 4;
const unsigned int MEMCHUNK_BITMASK_USED = 0x80000000;
const unsigned int MEMCHUNK_BITMASK_SIZE = 0x000fffff; // 20 bits for length means a maximum of 1 MB per chunk

#define CHUNK_INFO(_pChunk) (*(((unsigned int*)_pMemory) - 1))

void* pHeap;

//
//
//
void memChunkReset(void* _pMemory) {
    CHUNK_INFO(_pMemory) = 0;
}

//
// The low levels
//
void memChunkClrMask(void* _pMemory, unsigned int _Mask) {
    CHUNK_INFO(_pMemory) &= ~_Mask;
}

void memChunkSetMask(void* _pMemory, unsigned int _Mask) {
    CHUNK_INFO(_pMemory) |= _Mask;
}

unsigned int memChunkGetMasked(void* _pMemory, unsigned int _Mask) {
    return CHUNK_INFO(_pMemory) & _Mask;
}


//
// The meaningful, is used
//
void memChunkClrIsUsed(void* _pMemory) {
    memChunkClrMask(_pMemory, MEMCHUNK_BITMASK_USED);
}
                    
void memChunkSetIsUsed(void* _pMemory) {
    memChunkSetMask(_pMemory, MEMCHUNK_BITMASK_USED);
}

unsigned int memChunkGetIsUsed(void* _pMemory) {
    return memChunkGetMasked(_pMemory, MEMCHUNK_BITMASK_USED);
}

//
// The meaningful, size
//
void memChunkSetSize(void* _pMemory, unsigned int _Size) {
    memChunkClrMask(_pMemory, MEMCHUNK_BITMASK_SIZE);
    memChunkSetMask(_pMemory, _Size);
}

unsigned int memChunkGetSize(void* _pMemory) {
    return memChunkGetMasked(_pMemory, MEMCHUNK_BITMASK_SIZE);
}

//void* pFirstMemoryChunk;
//void* pNextFreeMemoryChunk;
//void* pEndOfMemory;


//
//
//
void* memChunkGetNext(void* _pMemory, void* _pEndOfMemory) {
    unsigned int size = memChunkGetSize(_pMemory);
    void* pRet = _pMemory + size + 4;
    if(pRet >= _pEndOfMemory) {
        return NULL;
    }
    
    return pRet;
}

void memInit(void* _pMemory, unsigned int _Size) {
    *(unsigned int*)_pMemory = _Size; // First 4 bytes of a memory area hold the size of the memory area
    
    _pMemory += MEMAREA_HEADER_SIZE + MEMCHUNK_HEADER_SIZE;
    
    memChunkReset(_pMemory); // This clears all the settings for the chunk
    memChunkClrIsUsed(_pMemory);
    memChunkSetSize(_pMemory, _Size - MEMAREA_HEADER_SIZE + MEMCHUNK_HEADER_SIZE);
}

void* memAlloc(void* _pMemory, unsigned int _Size) {
    unsigned int areaSize = *(unsigned int*)_pMemory;
    void* pEndOfMemory = _pMemory + areaSize;
    
    // Round required size to closest 4 for 4 byte alignment
    int allocatedMemorySizeAligned = (_Size+3) & 0x000ffffc;
    int allocatedMemorySizeAlignedPlusSplitHeader = allocatedMemorySizeAligned + 4;
    
    // Find first available chunk that meet required size
    void* pRet = _pMemory + 8;
    while(pRet != NULL) {
        int chunkUsed = memChunkGetIsUsed(pRet);
        int chunkSize = memChunkGetSize(pRet);
        if(chunkUsed == 0) {
            // This chunk is free
            if(chunkSize == allocatedMemorySizeAligned) {
                // This chunk is the exact right size
                break;
            } else if(chunkSize >= allocatedMemorySizeAlignedPlusSplitHeader) {
                // This chunk is big enough to fit
                // the needed size and a header for
                // a new chunk when split.
                break;
            }
        }
        
        //
        pRet = memChunkGetNext(pRet, pEndOfMemory);
    }

    // Didn't find any memory. Sad face!
    if(pRet == NULL) {
        return NULL;
    }
    
    // Do we need to split the previous chunk
    if(memChunkGetSize(pRet) > allocatedMemorySizeAlignedPlusSplitHeader) {
        // Need to split this chunk
        int splitChunkOriginalSize = memChunkGetSize(pRet);
        memChunkSetSize(pRet, allocatedMemorySizeAligned);
        
        void* pNewChunk = memChunkGetNext(pRet, pEndOfMemory);
        memChunkReset(pNewChunk);
        memChunkClrIsUsed(pNewChunk);
        memChunkSetSize(pNewChunk, splitChunkOriginalSize - allocatedMemorySizeAlignedPlusSplitHeader);
    }

    memChunkSetIsUsed(pRet);
    
    return pRet;
}

void memFree(void* _pMemory) {
    memChunkClrIsUsed(_pMemory);
}
