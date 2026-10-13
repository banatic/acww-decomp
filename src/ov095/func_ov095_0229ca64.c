/* func_ov095_0229ca64 @ 0x0229ca64, 0xf8 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

// Built at -O1,s. The last read-modify-write goes through a named pointer.

extern int func_ov095_0229c930(void *);
extern char *func_ov095_0229b16c(void *);

void func_ov095_0229ca64(void *o, int id, int val)
{
    char *base;
    u32 *q;

    if (func_ov095_0229c930(o) != 0) {
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
