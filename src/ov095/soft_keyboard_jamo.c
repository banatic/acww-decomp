/* soft_keyboard_jamo: 6 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229ba44 @ 0x0229ba44, 0xf0 bytes, Thumb
 * func_ov095_0229ba28 @ 0x0229ba28, 0x1c bytes, Thumb
 * func_ov095_0229ba0c @ 0x0229ba0c, 0x1c bytes, Thumb
 * func_ov095_0229b9e0 @ 0x0229b9e0, 0x2a bytes, Thumb
 * func_ov095_0229b8d8 @ 0x0229b8d8, 0x108 bytes, Thumb
 * func_ov095_0229b810 @ 0x0229b810, 0xc8 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229ba44 {
    u8 pad_00[4];
} UnkStruct_0229ba44;

extern void func_ov095_0229b3ec(UnkStruct_0229ba44 *self);
extern int func_ov095_0229bebc(UnkStruct_0229ba44 *self, int cmd);
extern void func_ov095_0229c104(UnkStruct_0229ba44 *self, int arg);
extern void func_ov095_0229c134(UnkStruct_0229ba44 *self, int arg);
extern void func_ov095_0229c178(UnkStruct_0229ba44 *self, int arg);
extern void func_ov095_0229c1c4(UnkStruct_0229ba44 *self, int cmd, int arg);
extern void func_0200467c(int a);

int func_ov095_0229ba44(UnkStruct_0229ba44 *self, int cmd, int arg)
{
    if (cmd == 0xa) {
        func_ov095_0229b3ec(self);
    }

    if (func_ov095_0229bebc(self, cmd) == 0) {
        func_ov095_0229c104(self, arg);
        return 0;
    }

    switch (cmd) {
        case 0x101:
        case 0x102:
            return 2;
        case 0x11f:
            func_ov095_0229c134(self, arg);
            func_0200467c(0x18);
            return 2;
        case 0x120:
            func_ov095_0229c178(self, arg);
            func_0200467c(0x18);
            return 2;
        case 0x107:
        case 0x108:
        case 0x109:
            func_ov095_0229c1c4(self, cmd, arg);
            func_0200467c(0x18);
            return 2;
        case 0x121:
        case 0x122:
        case 0x123:
            return 2;
        default:
            break;
    }
    func_ov095_0229c104(self, arg);
    return 0;
}

int func_ov095_0229ba28(int unused, unsigned int value)
{
    if (value >= 0x314F && value <= 0x3163) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov095_0229ba0c(void *unused, unsigned int key)
{
    if (key >= 0x3131 && key <= 0x314e) {
        return 1;
    }
    return 0;
}

int func_ov095_0229b9e0(void *a, void *b)
{
    if (func_ov095_0229ba28((int) a, (unsigned int) b) != 0 || func_ov095_0229ba0c(a, (unsigned int) b) != 0) {
        return 1;
    }
    return 0;
}

int func_ov095_0229b8d8(int arg0, unsigned int b)
{
    switch (b - 0x3131) {
        case 0:
            return 0xac00;
        case 1:
            return 0xae4c;
        case 3:
            return 0xb098;
        case 6:
            return 0xb2e4;
        case 7:
            return 0xb530;
        case 8:
            return 0xb77c;
        case 16:
            return 0xb9c8;
        case 17:
            return 0xbc14;
        case 18:
            return 0xbe60;
        case 20:
            return 0xc0ac;
        case 21:
            return 0xc2f8;
        case 22:
            return 0xc544;
        case 23:
            return 0xc790;
        case 24:
            return 0xc9dc;
        case 25:
            return 0xcc28;
        case 26:
            return 0xce74;
        case 27:
            return 0xd0c0;
        case 28:
            return 0xd30c;
        case 29:
            return 0xd558;
        default:
            if (b < 0x314f) {
                return 0;
            }
            return (unsigned short) ((b - 0x314f) * 28);
    }
}

int func_ov095_0229b810(int, int b)
{
    switch ((unsigned int) (b - 0x3131)) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 4;
        case 4:
            return 5;
        case 5:
            return 6;
        case 6:
            return 7;
        case 8:
            return 8;
        case 9:
            return 9;
        case 10:
            return 10;
        case 11:
            return 11;
        case 12:
            return 12;
        case 13:
            return 13;
        case 14:
            return 14;
        case 15:
            return 15;
        case 16:
            return 16;
        case 17:
            return 17;
        case 19:
            return 18;
        case 20:
            return 19;
        case 21:
            return 20;
        case 22:
            return 21;
        case 23:
            return 22;
        case 25:
            return 23;
        case 26:
            return 24;
        case 27:
            return 25;
        case 28:
            return 26;
        case 29:
            return 27;
        case 7:
        case 18:
        case 24:
        default:
            return 0;
    }
}
