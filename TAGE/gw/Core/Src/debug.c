#include "debug.h"
#include "draw.h"
#include "fontprint.h"
#include "mem.h"
#include "buttons.h"
#include "input.h"

int debugActive;

void debugInit()
{
    debugActive = 0;
}

int debugUpdate()
{
    if(inputDown(B_GAME)) {
        debugActive = !debugActive;
    }
    
    if(debugActive) {
        Cls(0x0000);
        fontprint("Dr. Debug", 0, 20, 0xf000);
    }
    
    return debugActive;
}
