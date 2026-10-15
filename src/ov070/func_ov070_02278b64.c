/* func_ov070_02278b64 @ 0x02278b64, 0x2cc bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Big {
    u8 pad_00[0x724];
    u8 arr724[0x14];
    u8 unk_738;
} Big;

typedef struct UnkStruct_02278b64 {
    u8 pad_00[0x1e];
    u8 state;
    u8 pad_1F[0x21];
    void *unk_40;
    u8 pad_44[0x70];
    Big *big;
} UnkStruct_02278b64;

typedef struct Loc {
    u8 a;
    u8 b;
    u16 c;
    u16 d;
} Loc;

extern void *func_020984e8(void);
extern int func_0209a1e8(void);
extern void *func_0209a1d0(void);
extern void *func_02099670(void *);
extern void *func_020b5630(void *);
extern void func_ov070_02279238(UnkStruct_02278b64 *);
extern u32 func_02088b64(void *);
extern int func_020154b4(UnkStruct_02278b64 *, u16 *, int, int, int);
extern int func_020b45d0(void *, u32, int, int, int, int);
extern int func_0203d7c4(int, void *);
extern int func_02099870(void *);
extern void func_02066024(void *, Loc *, void *, void *, void *, int);
extern u16 func_0204bd20(int, int);
extern int func_020996ac(void *);
extern int OS_UnlockByWord_IrqAndFiq(int object, u16 *item, int mode);
extern unsigned short func_02065ed0(void *, int, int);
extern void *func_020b5618(void *);
extern int func_ov070_02279724(Big *, u8 *, int);
extern int func_020644cc(int);
extern int func_ov070_022790cc(UnkStruct_02278b64 *);
extern void func_0208b520(void);
extern void func_020157c8(UnkStruct_02278b64 *, int, int);
extern int func_02015828(UnkStruct_02278b64 *, int);
extern void func_ov070_02279820(UnkStruct_02278b64 *, int);
extern void func_0208b514(void);
extern int func_ov070_02278e30(UnkStruct_02278b64 *);
extern int func_0202ea80(int, int);
extern void func_0204093c(int);
extern void func_0206844c(void *, u8 *, void *);
extern int func_02099710(void *);
extern int func_0206300c(int, int);
extern int func_020950c0(int);

extern int data_ov070_02279d24, data_ov070_02279d58, data_ov070_02279d20;

void func_ov070_02278b64(UnkStruct_02278b64 *self)
{
    void *ent;
    void *sub;
    void *txt;
    Loc loc;
    u32 buf[0x11];
    u8 v = 0xff;
    int st;
    int i;
    u8 n;
    u8 k;

    ent = func_020984e8();

    st = self->state;
    if (st >= 0xf && st <= 0x22) {
        k = self->big->unk_738;
        if (k < 5) {
            v = (u8) (k + 0x46);
        }
    }
    if (st == 0xe || (st >= 0x47 && st <= 0x4a)) {
        i = func_ov070_02279724(self->big, self->big->arr724, 0x14);
        if (self->big->arr724[i] == 0) {
            self->big->arr724[i] = 1;
        }
        v = (u8) (i + 0xf);
        self->big->unk_738++;
    }

    if (self->state == 0x24) {
        if (func_0209a1e8() != -1) {
            sub = func_0209a1d0();
            if (sub != 0) {
                txt = func_02099670(ent);
                func_020b5630(buf);
                n = 0;
                loc.a = n;
                func_ov070_02279238(self);
                if (func_02088b64(txt) > 0x15) {
                    n = (u8) ((u8) (func_02088b64(txt) - 0x15) / 10);
                }
                if (n > 7) {
                    n = 7;
                }
                loc.a = n;
                loc.c = 0x1565;
                func_020154b4(self, &loc.c, 0, 5, 0);
                func_020b45d0(buf, func_02088b64(txt), 10, 0, 0, 0);
                func_0203d7c4(0, buf);
                func_02066024(sub, &loc, &data_ov070_02279d58, &data_ov070_02279d20, &data_ov070_02279d24, func_02099870(ent));
                if (ent != 0) {
                    loc.d = func_0204bd20(0x10, 4);
                    OS_UnlockByWord_IrqAndFiq(func_020996ac(ent), &loc.d, 0);
                }
                if (n <= 2) {
                    func_02065ed0(sub, 0x12a7, 1);
                } else if (n <= 4) {
                    func_02065ed0(sub, 0x1248, 1);
                }
                func_020b5618(buf);
            }
        }
    }

    switch ((int) self->state) {
        case 0:
            if (func_0206300c(func_02099710(ent), 0) == 0x22) {
                if (func_020950c0(func_02099870(ent)) == 0) {
                    v = (u8) (func_020644cc(2) + 1);
                } else {
                    v = (u8) (func_020644cc(2) + 3);
                }
            } else {
                if (func_020950c0(func_02099870(ent)) == 0) {
                    v = (u8) (func_020644cc(2) + 5);
                } else {
                    v = (u8) (func_020644cc(2) + 7);
                }
            }
            break;
        case 0x25:
            v = (u8) (func_020644cc(0xa) + 0x3a);
            self->big->unk_738 = 0;
            break;
        case 0x28:
        case 0x2b:
            if (func_ov070_022790cc(self)) {
                v = 0x2c;
                func_0208b520();
            } else {
                v = 0x39;
            }
            break;
        case 0x2c:
        case 0x31:
            if (func_ov070_022790cc(self)) {
                func_020157c8(self, 0x39, 0);
                func_02015828(self, 2);
                func_ov070_02279820(self, 0);
            } else {
                v = 0x39;
            }
            break;
        case 0x36:
            func_0208b514();
            if (func_ov070_02278e30(self) == 0) {
                v = 0x37;
            } else {
                v = 0x34;
            }
            func_0202ea80(9, 1);
            break;
        case 0x38:
            func_0204093c(0x40);
            break;
    }

    if (v != 0xff) {
        loc.b = v;
        func_0206844c(self->unk_40, &loc.b, &data_ov070_02279d58);
    }
}
