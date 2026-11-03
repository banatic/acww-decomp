/* field_actor_4: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220cd08 @ 0x0220cd08, 0x7c bytes, Thumb
 * func_ov003_0220cc24 @ 0x0220cc24, 0xe4 bytes, Thumb
 * func_ov003_0220cbb4 @ 0x0220cbb4, 0x70 bytes, Thumb
 * func_ov003_0220ca24 @ 0x0220ca24, 0x190 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x5c];
    int pos[3];
    char pad_68[0x98 - 0x68];
    int unk_98;
    char pad_9C[0x8d8 - 0x9c];
    int unk_8D8;
    int unk_8DC;
} UnkStruct_0220cd08;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C[4];
    unsigned char pad_60[0x7f0 - 0x60];
    int unk_7F0;
    unsigned char pad_7F4[0x800 - 0x7f4];
    int unk_800;
    unsigned char pad_804[0x80c - 0x804];
    int unk_80C;
    unsigned char pad_810[0x8e0 - 0x810];
    int unk_8E0;
    int unk_8E4;
} UnkStruct_0220cc24;

struct UnkStruct_0220cbb4 {
    u8 pad_00[0x818];
    u32 unk_818;
    u8 pad_81C[0xc4];
    u32 unk_8E0;
    u32 unk_8E4;
};

typedef struct UnkStruct_0220ca24 {
    u8 pad_00[0x7f8];
    u32 unk_7F8;
} UnkStruct_0220ca24;

extern void func_0204f818(int *a, int *b, void *v);
extern void func_020448b8(int *p);
extern int func_0200f290(void *self, int param);
extern int func_0200ea0c(void *self, int param);
extern unsigned int func_0200fbe0(void *self);
extern int func_020438dc(int arg0, int *arg1, int arg2);
extern int func_0200ffec(void *self);
extern void func_0200e854(void *self);
extern unsigned int *func_0200f27c(void *self, int param);
extern void func_0200f268(struct UnkStruct_0220cbb4 *self, int param);
extern int func_ov003_0220e8f4(struct UnkStruct_0220cbb4 *self, u32 *arr, int a, int b);
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

void func_ov003_0220cd08(UnkStruct_0220cd08 *self)
{
    volatile int a = 0, b = 0;
    unsigned int ok;
    int va;
    int t[2];

    if (self->unk_98 > 0x53f) {
        func_0204f818((int *) &a, (int *) &b, self->pos);
        ok = 0;
        va = a;
        if (a == self->unk_8D8 && b == self->unk_8DC) {
            ok = 1;
        }
        if (ok > 0) {
            self->unk_8D8 = va;
            self->unk_8DC = b;
        } else {
            self->unk_8D8 = va;
            self->unk_8DC = b;
            t[0] = a;
            t[1] = b;
            func_020448b8(t);
        }
    }
}

void func_ov003_0220cc24(UnkStruct_0220cc24 *self)
{
    int a, b;
    int pair[2];
    unsigned int idx;
    int mode;

    if (func_0200f290(self, 11) != 0) {
        return;
    }
    if (func_0200f290(self, 22) != 0) {
        return;
    }
    if (func_0200ea0c(self, self->unk_7F0) == 0) {
        return;
    }
    if (self->unk_80C != -1) {
        return;
    }

    a = 0;
    b = 0;
    func_0204f818(&a, &b, self->unk_5C);

    idx = func_0200fbe0(self);
    mode = 0;
    switch (idx) {
        case 1:
            mode = 2;
            break;
        case 2:
            mode = 1;
            break;
        case 4:
            mode = 3;
            break;
        case 5:
            mode = 4;
            break;
    }

    pair[0] = a;
    pair[1] = b;
    self->unk_80C = func_020438dc(self->unk_800, pair, mode);
    if (self->unk_80C == -1) {
        return;
    }

    if (func_0200ffec(self) != 0x19) {
        return;
    }
    func_0200e854(self);
    func_0200f27c(self, 0x16);
    func_0200f27c(self, 0x13);

    self->unk_8E0 = a;
    self->unk_8E4 = b;
}

void func_ov003_0220cbb4(struct UnkStruct_0220cbb4 *self)
{
    if (func_0200f290((void *) self, 0x16) == 0) {
        return;
    }

    switch (self->unk_818) {
        case 1: {
            u32 arr[2];
            arr[0] = self->unk_8E0;
            arr[1] = self->unk_8E4;
            func_ov003_0220e8f4(self, arr, 6, -1);
            func_0200f268(self, 0x16);
            func_0200f268(self, 0x13);
            break;
        }
        case 2:
            func_0200f268(self, 0x16);
            func_0200f268(self, 0x13);
            break;
        default:
            break;
    }
}

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
