/* func_ov095_0229c654 @ 0x0229c654, 0xfa bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int _s32_div_f(int a, int b);

int func_ov095_0229c654(int a1, unsigned short a2, unsigned short a3)
{
    if (a3 < 0x60) {
        return -1;
    }
    if (a3 >= 0xb0) {
        return -1;
    }
    if (a3 < 0x70) {
        if (a2 < 4) {
            return -1;
        }
        if (a2 < 0xcc) {
            return _s32_div_f(a2 - 4, 0x14) + 0xc9;
        }
        return -1;
    }
    if (a3 < 0x80) {
        if (a2 < 0xc) {
            return -1;
        }
        if (a2 < 0xd4) {
            return _s32_div_f(a2 - 0xc, 0x14) + 0xd3;
        }
        if (a2 < 0xfc) {
            return 0xdd;
        }
        return -1;
    }
    if (a3 < 0x90) {
        if (a2 < 0x18) {
            return -1;
        }
        if (a2 < 0xcc) {
            return _s32_div_f(a2 - 0x18, 0x14) + 0xde;
        }
        if (a2 < 0xfc) {
            return 0xe7;
        }
        return -1;
    }
    if (a3 < 0xa0) {
        if (a2 < 0x20) {
            return -1;
        }
        if (a2 < 0xe8) {
            return _s32_div_f(a2 - 0x20, 0x14) + 0xe8;
        }
        return -1;
    }
    if (a2 < 0x28) {
        return -1;
    }
    if (a2 < 0x3c) {
        return 0xf2;
    }
    if (a2 < 0x50) {
        return 0xf3;
    }
    if (a2 < 0xa8) {
        return 0xf4;
    }
    if (a2 < 0xbc) {
        return 0xf5;
    }
    if (a2 < 0xd0) {
        return 0xf6;
    }
    return -1;
}
