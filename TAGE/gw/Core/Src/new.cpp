#include "new.h"
#include "mem.h"

void* operator new(unsigned int _size) {
	return memAlloc(pHeap, _size);
}

void operator delete(void* _pMem, unsigned int _wha) {
	memFree(_pMem);
}
