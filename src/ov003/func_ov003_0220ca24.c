/* func_ov003_0220ca24 @ 0x0220ca24, 0x190 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0220ca24 {
    u8 pad_00[0x7f8];
    u32 unk_7F8;
} UnkStruct_0220ca24;

extern int func_0200ee0c(UnkStruct_0220ca24 *);
extern u16 *func_02096274(void);
extern u8 *func_0209626c(void);
extern int func_02011368(UnkStruct_0220ca24 *);
extern void func_0209e474(u32 *);
extern int func_0200f86c(UnkStruct_0220ca24 *);
extern int func_020ba4d4(void);
extern void func_020110c4(volatile u16 *, UnkStruct_0220ca24 *);
extern void func_020997b4(int, u8);
extern void func_0200f7ac(UnkStruct_0220ca24 *, int, u16 *);
extern u8 func_020112bc(UnkStruct_0220ca24 *);
extern void func_0200f11c(UnkStruct_0220ca24 *);

void func_ov003_0220ca24(UnkStruct_0220ca24 *obj)
{
    u16 *cnt;
    u8 *fl;
    int sp4;
    int v5;
    unsigned int sp0;
    unsigned int ok;
    u16 lo, hi;
    unsigned int b2, b3, b4;
    u8 ret;
    u16 temp;
    volatile u16 x;
    volatile u16 y;
    u32 arr[2];

    if (obj->unk_7F8 == 0) {
        return;
    }

    sp0 = 0;
    if (func_0200ee0c(obj) != 0) {
        sp0 = 1;
    }

    cnt = func_02096274();
    if (*cnt == 0) {
        *cnt = 1;
    }
    fl = func_0209626c();
    sp4 = func_02011368(obj);

    arr[0] = 0;
    arr[1] = 0;
    func_0209e474(arr);

    if ((*fl & 1) != 0) {
        if (func_0200f86c(obj) != 1) {
            return;
        }
        if (sp0 != 0) {
            *fl = *fl & 0xfe;
        } else {
            *fl = *fl & 0xee;
        }
    }

    v5 = ((u8 *) arr)[5];
    b4 = ((u8 *) arr)[4];
    b3 = ((u8 *) arr)[3];
    if (!(b4 == 8 || (b4 == 7 && b3 >= 0x10) || (b4 == 9 && b3 <= 0xf))) {
        return;
    }

    b2 = ((u8 *) arr)[2];
    if (b2 < 0xa || b2 >= 0x11) {
        return;
    }
    if (func_020ba4d4() >= 3) {
        return;
    }

    func_020110c4(&x, obj);
    ok = 0;
    lo = x;
    hi = x;
    if (hi >= 0x1380 && lo <= 0x139f) {
        ok = 1;
    }
    if (ok != 0) {
        return;
    }

    func_020110c4(&y, obj);
    ok = 0;
    lo = y;
    hi = y;
    if (hi >= 0x13a0 && lo <= 0x13a7) {
        ok = 1;
    }
    if (ok != 0) {
        return;
    }

    *cnt = *cnt - 1;
    if (*cnt != 0) {
        return;
    }

    temp = (u16) ((temp & ~0x7f) | (v5 & 0x7f));
    temp = (u16) ((temp & ~0x780) | ((b4 & 0xf) << 7));
    temp = (u16) ((temp & ~0xf800) | ((b3 & 0x1f) << 11));

    ret = (u8) (func_020112bc(obj) + 1);
    if (ret > 7) {
        ret = 7;
    }
    func_020997b4(sp4, ret);
    func_0200f7ac(obj, sp4, &temp);
    *cnt = 0x4650;
    *fl = *fl & 0xfb;
    *fl = *fl | 3;
    func_0200f11c(obj);
}
