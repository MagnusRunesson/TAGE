#include "test.h"
#include "new.h"

CTest::CTest() {
	j = 10;
}

CTest* testFunc(void) {
	return new CTest();
}

