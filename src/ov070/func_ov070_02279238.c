/* func_ov070_02279238 @ 0x02279238, 0x214 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02279238 {
    char pad_00[0xc4];
    u16 unk_C4;
    u16 unk_C6;
    u16 unk_C8;
} UnkStruct_02279238;

extern int func_020984e8(void);
extern int func_02099670(void);
extern u16 *func_020996f8(int);
extern u16 *func_020996e0(int);
extern u16 *func_02099710(int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_0204c878(u16 *);
extern int func_ov070_0227944c(UnkStruct_02279238 *, int, int);
extern void func_02088b50(int, u8);
extern int func_020644cc(int);

void func_ov070_02279238(UnkStruct_02279238 *self)
{
    u16 tmp[3];
    int g;
    int h;
    int t;
    int ok;
    int flag;
    int c;

    g = func_020984e8();
    h = func_02099670();

    self->unk_C4 = *func_020996f8(g);
    if (func_0204bcdc(&self->unk_C4) != 0) {
        tmp[0] = 0xfff1;
        t = func_0204bc64(&self->unk_C4);
        if (t == func_0204bc64(&tmp[0])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (self->unk_C4 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        flag = 0;
        if (self->unk_C4 >= 0x1429 && self->unk_C4 <= 0x1430) {
            flag = 1;
        }
        if (flag == 0) {
            func_02088b50(h, (u8) (func_ov070_0227944c(self, func_0204c878(&self->unk_C4), 0) * 2));
        } else {
            func_02088b50(h, (u8) ((func_020644cc(0xa) + 1) * 2));
        }
    } else {
        c = func_020644cc(3);
        func_02088b50(h, (u8) ((u8) (c + 1) * 2));
    }

    self->unk_C6 = *func_020996e0(g);
    if (func_0204bcdc(&self->unk_C6) != 0) {
        tmp[1] = 0xfff1;
        t = func_0204bc64(&self->unk_C6);
        if (t == func_0204bc64(&tmp[1])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (self->unk_C6 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        func_02088b50(h, (u8) (func_ov070_0227944c(self, func_0204c878(&self->unk_C6), 1) * 2));
    } else {
        c = func_020644cc(3);
        func_02088b50(h, (u8) ((u8) (c + 1) * 2));
    }

    self->unk_C8 = *func_02099710(g);
    if (func_0204bcdc(&self->unk_C8) != 0) {
        tmp[2] = 0xfff1;
        t = func_0204bc64(&self->unk_C8);
        if (t == func_0204bc64(&tmp[2])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (self->unk_C8 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        flag = 0;
        if (self->unk_C4 >= 0x12a8 && self->unk_C4 <= 0x12af) {
            flag = 1;
        }
        if (flag == 0) {
            func_02088b50(h, (u8) (func_ov070_0227944c(self, func_0204c878(&self->unk_C8), 2) * 2));
        } else {
            func_02088b50(h, (u8) ((func_020644cc(0xa) + 1) * 2));
        }
    }
}
