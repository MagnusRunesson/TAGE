#include "input.h"
#include "buttons.h"

unsigned int buttonNow;
unsigned int buttonPrevious;
unsigned int buttonDown;
unsigned int buttonUp;

void inputInit() {
    buttonDown = buttonUp = 0;
    buttonNow = buttonPrevious = buttons_get();
}

void inputUpdate() {
    buttonPrevious = buttonNow;
    buttonNow = buttons_get();
    unsigned int buttonDiff = buttonPrevious ^ buttonNow;
    buttonDown = buttonNow & buttonDiff;
    buttonUp = buttonPrevious & buttonDiff;
}

int inputDown(int _buttonMask) {
    return buttonDown & _buttonMask;
}

inline int inputUp(int _buttonMask) {
    return buttonUp & _buttonMask;
}

inline int inputNow(int _buttonMask) {
    return buttonNow & _buttonMask;
}
