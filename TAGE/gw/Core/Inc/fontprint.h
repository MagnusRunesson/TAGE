#pragma once

#ifdef __cplusplus
extern "C" {
#endif

char* vtoaui(unsigned int _i, int _base, int _padding);
char* vtoasi(int _i, int _base, int _padding);

void fontprint(const char* _pszMessage, int _x, int _y, unsigned short color);

#ifdef __cplusplus
}
#endif
