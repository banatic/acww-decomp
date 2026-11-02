/* soft_keyboard_palettes: 2 functions, module ov095
 * mwccarm 1.2/base -O1,s
 * func_ov095_0229cb5c @ 0x0229cb5c, 0x140 bytes, Thumb
 * func_ov095_0229ca64 @ 0x0229ca64, 0xf8 bytes, Thumb
 */

#include "types.h"

extern int func_ov095_0229c930(void *, int unused1, int unused2);
extern char *func_ov095_0229b16c(void *);

void func_ov095_0229cb5c(void *o, int id, int val)
{
    char *base;
    u32 *q;

    if (func_ov095_0229c930(o, id, val) != 0) {
        return;
    }
    if (id < 0x3b) {
        return;
    }
    if (id > 0x6f) {
        return;
    }
    base = func_ov095_0229b16c(o);
    if (id >= 0x3b && id <= 0x46) {
        id -= 0x3b;
    } else if (id >= 0x47 && id <= 0x50) {
        id -= 0x3b;
    } else if (id == 0x51) {
        id = 0x16;
        *(u32 *) (base + 0xbc) = (*(u32 *) (base + 0xbc) & 0xffff0fff) | ((val & 0xf) << 12);
    } else if (id >= 0x52 && id <= 0x5b) {
        id -= 0x3a;
    } else if (id == 0x5c) {
        id = 0x22;
        *(u32 *) (base + 0x11c) = (*(u32 *) (base + 0x11c) & 0xffff0fff) | ((val & 0xf) << 12);
        *(u32 *) (base + 0x124) = (*(u32 *) (base + 0x124) & 0xffff0fff) | ((val & 0xf) << 12);
    } else if (id >= 0x5d && id <= 0x67) {
        id -= 0x38;
    } else if (id >= 0x68 && id <= 0x69) {
        id -= 0x38;
    } else if (id == 0x6b) {
        id = 0x32;
        *(u32 *) (base + 0x19c) = (*(u32 *) (base + 0x19c) & 0xffff0fff) | ((val & 0xf) << 12);
        *(u32 *) (base + 0x1a4) = (*(u32 *) (base + 0x1a4) & 0xffff0fff) | ((val & 0xf) << 12);
        *(u32 *) (base + 0x1ac) = (*(u32 *) (base + 0x1ac) & 0xffff0fff) | ((val & 0xf) << 12);
        *(u32 *) (base + 0x1b4) = (*(u32 *) (base + 0x1b4) & 0xffff0fff) | ((val & 0xf) << 12);
        *(u32 *) (base + 0x1bc) = (*(u32 *) (base + 0x1bc) & 0xffff0fff) | ((val & 0xf) << 12);
    } else if (id >= 0x6e && id <= 0x6f) {
        id -= 0x36;
    } else {
        return;
    }
    q = (u32 *) (base + id * 8 + 4);
    *q = (*q & 0xffff0fff) | ((val & 0xf) << 12);
}

// Built at -O1,s. The last read-modify-write goes through a named pointer.

void func_ov095_0229ca64(void *o, int id, int val)
{
    char *base;
    u32 *q;

    if (func_ov095_0229c930(o, id, val) != 0) {
        return;
    }
    if (id < 0x70) {
        return;
    }
    if (id > 0x91) {
        return;
    }
    base = func_ov095_0229b16c(o);
    if (id >= 0x70 && id <= 0x79) {
        id -= 0x70;
    } else if (id >= 0x7a && id <= 0x83) {
        id -= 0x6e;
    } else if (id >= 0x84 && id <= 0x8d) {
        id -= 0x6c;
    } else {
        switch (id) {
            case 0x8e:
                id = 0xa;
                break;
            case 0x8f:
                id = 0xb;
                break;
            case 0x90:
                id = 0x16;
                *(u32 *) (base + 0xbc) = (*(u32 *) (base + 0xbc) & 0xffff0fff) | ((val & 0xf) << 12);
                break;
            case 0x91:
                id = 0x22;
                *(u32 *) (base + 0x11c) = (*(u32 *) (base + 0x11c) & 0xffff0fff) | ((val & 0xf) << 12);
                *(u32 *) (base + 0x124) = (*(u32 *) (base + 0x124) & 0xffff0fff) | ((val & 0xf) << 12);
                *(u32 *) (base + 0x12c) = (*(u32 *) (base + 0x12c) & 0xffff0fff) | ((val & 0xf) << 12);
                *(u32 *) (base + 0x134) = (*(u32 *) (base + 0x134) & 0xffff0fff) | ((val & 0xf) << 12);
                break;
            default:
                return;
        }
    }
    q = (u32 *) (base + id * 8 + 4);
    *q = (*q & 0xffff0fff) | ((val & 0xf) << 12);
}
