#pragma once

#if __cplusplus
extern "C" {
#endif

    void inputInit();
    void inputUpdate();
    int inputDown(int _buttonMask);
    int inputUp(int _buttonMask);
    int inputNow(int _buttonMask);

#ifdef __cplusplus
}
#endif
