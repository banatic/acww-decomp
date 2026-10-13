/* func_ov003_02217e30 @ 0x02217e30, 0x2d8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02217e30 {
    u8 pad_00[0x2d0];
    u8 sub_2d0[0x7d4 - 0x2d0];
    u8 unk_7D4;
    u8 pad_7D5[0x7f0 - 0x7d5];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
} UnkStruct_02217e30;

extern void *data_020ccf94;

extern int func_02056f94(void *p);
extern void func_0200f3e8(UnkStruct_02217e30 *self);
extern int func_02008258(UnkStruct_02217e30 *self, int a);
extern void func_020110c4(volatile u16 *out, UnkStruct_02217e30 *self);
extern void func_0200f268(UnkStruct_02217e30 *self, int a);
extern void func_0200f27c(UnkStruct_02217e30 *self, int a);
extern int func_0200f290(UnkStruct_02217e30 *self, int a);
extern int func_0204bcdc(volatile u16 *p);
extern int func_0204bc64(volatile u16 *p);
extern int func_020b22dc(void);
extern int func_02073908(void *g, int a);
extern void func_ov003_02217c5c(UnkStruct_02217e30 *self, int a, int b, int c, int d, int e, int f, int g);
extern void func_020094a0(UnkStruct_02217e30 *self, int a, int b, int c, int d, int e);
extern void func_0203e110(void);
extern void func_0200d4e8(UnkStruct_02217e30 *self, int a, int b, int c);
extern int func_0208602c(void);
extern void func_020860d4(int h, int a);
extern int func_020984e8(void);
extern void func_02098fd0(int h, int a);
extern void func_02042500(void);

void func_ov003_02217e30(UnkStruct_02217e30 *self)
{
    volatile u16 a;
    volatile u16 b;
    volatile u16 t1;
    volatile u16 t2;
    volatile u16 t3;
    volatile u16 t4;
    u8 *st;
    u8 state;
    void *g;
    int c;

    if (func_02056f94(self->sub_2d0) == 0) {
        return;
    }

    func_0200f3e8(self);
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    st = &self->unk_7D4;
    state = *st;
    func_020110c4(&a, self);

    if (state <= 1) {
        int ok = 0;
        u16 x = a;
        u16 y = a;
        if (y >= 0x1380 && x <= 0x139f) {
            ok = 1;
        }
        if (ok != 0 || (x >= 0x13a0 && x <= 0x13a7)) {
            func_0200f268(self, 0x1d);
        }
    }

    switch (*st) {
        case 0:
            if (func_0204bcdc(&a) != 0) {
                t4 = 0xfff1;
                if (func_0204bc64(&a) == func_0204bc64(&t4)) {
                    c = 1;
                } else {
                    c = 0;
                }
            } else {
                if (a == 0xfff1) {
                    c = 1;
                } else {
                    c = 0;
                }
            }
            if (c == 0 && func_020b22dc() == 0 && func_0200f290(self, 0x1d) == 0) {
                func_ov003_02217c5c(self, 2, 2, 0, 0, 0, 6, -1);
                break;
            }
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                if (func_0204bcdc(&a) != 0) {
                    t1 = 0xfff1;
                    if (func_0204bc64(&a) == func_0204bc64(&t1)) {
                        c = 1;
                    } else {
                        c = 0;
                    }
                } else {
                    if (a == 0xfff1) {
                        c = 1;
                    } else {
                        c = 0;
                    }
                }
                if (c != 0) {
                    func_0200f27c(self, 0);
                }
            }
            // fall through
        case 1:
            if (func_0204bcdc(&a) != 0) {
                t2 = 0xfff1;
                if (func_0204bc64(&a) == func_0204bc64(&t2)) {
                    c = 1;
                } else {
                    c = 0;
                }
            } else {
                if (a == 0xfff1) {
                    c = 1;
                } else {
                    c = 0;
                }
            }
            if (c != 0) {
                func_0200f27c(self, 0);
            }
            func_0203e110();
            func_0200f268(self, 0x1d);
            func_0200d4e8(self, 3, 1, -1);
            break;
        case 2:
            g = data_020ccf94;
            if (func_02073908(g, self->unk_800) != 0) {
                func_020860d4(func_0208602c(), 0);
            }
            if (func_020b22dc() == 0) {
                func_020094a0(self, 2, 0, 0, 6, -1);
                break;
            }
            func_0203e110();
            if (func_02073908(g, self->unk_800) != 0) {
                goto notify;
            }
            func_020110c4(&b, self);
            if (func_0204bcdc(&b) != 0) {
                t3 = 0xfff1;
                if (func_0204bc64(&b) == func_0204bc64(&t3)) {
                    c = 1;
                } else {
                    c = 0;
                }
            } else {
                if (b == 0xfff1) {
                    c = 1;
                } else {
                    c = 0;
                }
            }
            if (c == 0) {
                goto done;
            }
        notify:
            func_0200f27c(self, 0);
        done:
            func_0200f268(self, 0x1d);
            func_0200d4e8(self, 3, 1, -1);
            break;
        case 3:
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                func_020860d4(func_0208602c(), 5);
                func_02098fd0(func_020984e8(), 1);
                func_02042500();
            }
            func_020094a0(self, 3, 0, 0, 6, -1);
            break;
    }
}
