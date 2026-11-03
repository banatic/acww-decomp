/* post_clerk: 7 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_0226066c @ 0x0226066c, 0xa4 bytes, Thumb
 * func_ov054_022604d0 @ 0x022604d0, 0x19c bytes, Thumb
 * func_ov054_02260498 @ 0x02260498, 0x38 bytes, Thumb
 * func_ov054_02260484 @ 0x02260484, 0x14 bytes, Thumb
 * func_ov054_02260474 @ 0x02260474, 0x10 bytes, Thumb
 * func_ov054_02260448 @ 0x02260448, 0x2c bytes, Thumb
 * func_ov054_02260420 @ 0x02260420, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

typedef struct UnkStruct_0226066c UnkStruct_0226066c;

typedef struct UnkStruct_0226066c_2 UnkStruct_0226066c_2;

struct UnkStruct_0226066c {
    u8 unk_00[0x618];
    int unk_618;
    u8 p1[0x654 - 0x61c];
    int unk_654;
    u8 p2[0x80c - 0x658];
    int unk_80C;
};

struct UnkStruct_0226066c_2 {
    u8 unk_00[0x5c];
    Vec unk_5C;
};

typedef struct UnkStruct_022604d0_2 UnkStruct_022604d0_2;

typedef struct SubVT {
    void (*unk_00)(UnkStruct_022604d0_2 *);
    void (*unk_04)(UnkStruct_022604d0_2 *);
    void (*unk_08)(UnkStruct_022604d0_2 *);
} SubVT;

struct UnkStruct_022604d0_2 {
    const SubVT *vt;
};

typedef struct UnkStruct_022604d0_3 UnkStruct_022604d0_3;

struct UnkStruct_022604d0_3 {
    u8 pad_00[0x560];
    u8 mode;
    u8 pad_561[0x658 - 0x561];
    UnkStruct_022604d0_2 sub;
};

typedef struct UnkStruct_022604d0 {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_022604d0;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02260484;

typedef struct UnkStruct_02260448 {
    void *vtable;
    char pad_04[0x654];
    char sub[1];
} UnkStruct_02260448;

extern Vec data_ov054_022629c8[];
extern void func_0204f818(int *, int *, Vec *);
extern int func_02014868(int *);
extern int func_0201c014(UnkStruct_0226066c *);
extern UnkStruct_022604d0 *data_020ccf94;
extern void func_0201c054(UnkStruct_022604d0_3 *, int, int, int);
extern int func_0201c0e0(UnkStruct_022604d0_3 *);
extern int func_0201c2a4(UnkStruct_022604d0_3 *, int);
extern void func_02016108(UnkStruct_022604d0_2 *, int);
extern void func_ov054_02262528(UnkStruct_022604d0_3 *, int);
extern int func_020a7278(void);
extern int func_0201c040(UnkStruct_022604d0_3 *, int *, int *);
extern int func_0201a3e4(int);
extern int func_ov004_02225a14(void);
extern unsigned char func_02073dd4(UnkStruct_02260484 *p, int val);
extern int func_02073d90(int);
extern char data_ov054_02263094;
extern void *func_ov054_02261f98(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

int func_ov054_0226066c(UnkStruct_0226066c *self, UnkStruct_0226066c_2 *p)
{
    int result;
    int a, b, c, d;
    Vec v, w;
    Vec *sv;
    Vec *sw;

    result = 0;
    sv = &p->unk_5C;
    v.x = sv->x;
    v.y = sv->y;
    v.z = sv->z;
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    func_0204f818(&a, &b, &v);
    sw = &data_ov054_022629c8[self->unk_80C];
    w.x = sw->x;
    w.y = sw->y;
    w.z = sw->z;
    func_0204f818(&c, &d, &w);
    if (func_02014868(&self->unk_618) != 0 || func_0201c014(self) != 0) {
        return 0;
    }
    if (self->unk_654 == 2 || self->unk_654 == 0 || self->unk_654 == 9) {
        if (a == c) {
            if (b == d) {
                result = 1;
            }
        }
    }
    return result;
}

void func_ov054_022604d0(UnkStruct_022604d0_3 *self, int ev, int v)
{
    int a, b;
    int t;

    switch (ev) {
        case 3:
            self->mode = (u8) v;
            if (v != 4) {
                func_0201c054(self, 1, data_020ccf94->unk_64, v);
                func_ov054_02262528(self, 0xb);
            } else if (func_0201c0e0(self)) {
                t = data_020ccf94->unk_64;
                func_0201c054(self, 1, t, t);
                func_ov054_02262528(self, 0xb);
            }
            break;
        case 1:
            self->sub.vt->unk_08(&self->sub);
            func_02016108(&self->sub, func_0201c2a4(self, 4));
            func_ov054_02262528(self, 1);
            break;
        case 0:
            self->mode = (u8) v;
            if (v != 4 && v != data_020ccf94->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov054_02262528(self, 0xa);
            } else if (func_0201c0e0(self)) {
                t = data_020ccf94->unk_64;
                func_0201c054(self, 1, t, t);
                self->sub.vt->unk_08(&self->sub);
                func_02016108(&self->sub, func_0201c2a4(self, 4));
                func_ov054_02262528(self, 4);
            }
            break;
        case 8:
            if (v == 4) {
                if (func_020a7278()) {
                    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
                    func_ov054_02262528(self, 2);
                } else {
                    func_0201c054(self, 1, 4, data_020ccf94->unk_64);
                    func_ov054_02262528(self, 9);
                }
            }
            break;
        case 4:
            if (func_0201c014((UnkStruct_0226066c *) self) && func_0201c0e0(self)) {
                a = 4;
                b = 4;
                if (func_0201c040(self, &a, &b)) {
                    if (v != 4) {
                        if (v == b) {
                            goto ok4;
                        }
                    }
                    if (v != 4) {
                        return;
                    }
                ok4:
                    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
                    func_ov054_02262528(self, 2);
                }
            }
            break;
    }
}

int func_ov054_02260498(int arg0)
{
    int val;
    int val2;

    val = func_0201a3e4(arg0 + 0x2ac);
    if (val == 0xba) {
        val2 = func_ov004_02225a14();
        if (val2 != 0) {
            val = *(int *) (*(int *) (arg0 + 0x698) + 4);
            if (val == 2) {
                return 1;
            }
        }
    }
    return 0;
}

unsigned char func_ov054_02260484(void *receiver)
{
    return func_02073dd4((*(UnkStruct_02260484 * *) &data_020ccf94), (*(UnkStruct_02260484 * *) &data_020ccf94)->unk_64);
}

int func_ov054_02260474(void *self)
{
    return func_02073d90((*(int *) &data_020ccf94));
}

void *func_ov054_02260448(void *self)
{
    UnkStruct_02260448 *s;
    s = (UnkStruct_02260448 *) self;
    s->vtable = &data_ov054_02263094;
    func_ov054_02261f98(s->sub);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}

void *func_ov054_02260420(void *self)
{
    *(int *) self = (int) ((int *) &data_ov054_02263094);
    func_ov054_02261f98((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
