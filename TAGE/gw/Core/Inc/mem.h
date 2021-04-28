#pragma once

#define NULL ((void*)0)

#if __cplusplus
extern "C" {
#endif

	extern void* pHeap;
	
    void memInit(void* _pMemory, unsigned int _Size);
    void* memAlloc(void* _pMemory, unsigned int _Size);
    void memFree(void* _pMemory);

    void memChunkReset(void* _pMemory);
    void memChunkClrMask(void* _pMemory, unsigned int _Mask);
    void memChunkSetMask(void* _pMemory, unsigned int _Mask);
    unsigned int memChunkGetMasked(void* _pMemory, unsigned int _Mask);
    
    //
    // The meaningful, is used
    //
    void memChunkClrIsUsed(void* _pMemory);
    void memChunkSetIsUsed(void* _pMemory);
    unsigned int memChunkGetIsUsed(void* _pMemory);
    
    //
    // The meaningful, size
    //
    void memChunkSetSize(void* _pMemory, unsigned int _Size);
    unsigned int memChunkGetSize(void* _pMemory);
    
    //
    //
    //
    void* memChunkGetNext(void* _pMemory, void* _pEndOfMemory);

#ifdef __cplusplus
}
#endif
