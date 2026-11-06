/* museum_room_setup_3: 16 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02245648 @ 0x02245648, 0x2 bytes, Thumb
 * func_ov004_02245590 @ 0x02245590, 0xb8 bytes, Thumb
 * func_ov004_02245558 @ 0x02245558, 0x36 bytes, Thumb
 * func_ov004_02245554 @ 0x02245554, 0x2 bytes, Thumb
 * func_ov004_0224554c @ 0x0224554c, 0x6 bytes, Thumb
 * func_ov004_02245548 @ 0x02245548, 0x4 bytes, Thumb
 * func_ov004_02245544 @ 0x02245544, 0x4 bytes, Thumb
 * func_ov004_0224553c @ 0x0224553c, 0x6 bytes, Thumb
 * func_ov004_02245538 @ 0x02245538, 0x4 bytes, Thumb
 * func_ov004_02245534 @ 0x02245534, 0x4 bytes, Thumb
 * func_ov004_0224551c @ 0x0224551c, 0x18 bytes, Thumb
 * func_ov004_022454fc @ 0x022454fc, 0x20 bytes, Thumb
 * func_ov004_022454dc @ 0x022454dc, 0x20 bytes, Thumb
 * func_ov004_022454bc @ 0x022454bc, 0x20 bytes, Thumb
 * func_ov004_02245494 @ 0x02245494, 0x28 bytes, Thumb
 * func_ov004_02245474 @ 0x02245474, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02245590 {
    int x, y, z;
    int unk_0C;
    short unk_10;
    short unk_12;
    int unk_14;
    unsigned char unk_18;
    unsigned char unk_19;
} UnkStruct_02245590;

typedef struct {
    int a, b, c;
} UnkStruct_02245558;

typedef struct {
    unsigned char pad_00[12];
    unsigned long unk_0C;
} UnkStruct_02245548;

typedef struct {
    unsigned char pad_00[25];
    unsigned char unk_19;
} UnkStruct_02245544;

typedef struct {
    unsigned char pad_00[20];
    unsigned long unk_14;
} UnkStruct_02245538;

typedef struct {
    unsigned char pad_00[24];
    unsigned char unk_18;
} UnkStruct_02245534;

extern int FX_Div(int a, int b);
extern int func_020e8b4c(int a, int b);
extern int func_020edf70(int);
extern void *func_020ee660(void *);
extern void func_020ee62c(void *ptr);
extern void *const data_ov004_0225672c[];
extern void *const data_020da13c[];
extern void func_020edf54(void *p);

void *func_ov004_022454dc(void *self);

void func_ov004_02245648(void *object) {}

void func_ov004_02245590(UnkStruct_02245590 *o, Vec3 *src, int mask, int k, short a4, int a5, unsigned char a6)
{
    int best;
    int n;
    int sum;
    unsigned int i;
    int v;
    int last;
    // ENDDECLS
    o->x = src->x;
    o->y = src->y;
    o->z = src->z;
    o->unk_19 = (unsigned char) k;
    o->unk_12 = a4;
    o->unk_14 = a5;
    o->unk_18 = a6;
    sum = 0;
    n = 0;
    last = 0;
    for (i = 0; i < 4; i++) {
        if (((mask >> i) & 1) != 0) {
            sum = sum + (i << 14);
            last = (short) (i << 14);
            n++;
        }
    }
    o->unk_10 = (short) (FX_Div(sum << 12, n << 12) >> 12);
    if (n == 2) {
        if (func_020e8b4c(last, o->unk_10) >= 0x4000) {
            o->unk_10 = (short) (o->unk_10 + 0x8000);
        }
    }
    best = 0;
    for (i = 0; i < 4; i++) {
        if (((mask >> i) & 1) != 0) {
            v = func_020e8b4c((short) (i << 14), o->unk_10);
            if (v > best) {
                best = v;
            }
        }
    }
    o->unk_0C = best + 0x1300;
}

void *func_ov004_02245558(void *self, char *p)
{
    UnkStruct_02245558 t;
    int x = *(int *) (p + 8), y = *(int *) (p + 4), z = *(int *) p;
    t.a = z;
    t.b = y;
    t.c = x;
    func_ov004_02245590((UnkStruct_02245590 *) self, (Vec3 *) (&t), *(u8 *) (p + 0xc), *(u8 *) (p + 0xd), *(short *) (p + 0xe),
                        *(int *) (p + 0x10), *(u8 *) (p + 0x14));
    return self;
}

unsigned int *func_ov004_02245554(void *record)
{
    return (unsigned int *) record;
}

int func_ov004_0224554c(void *self)
{
    return *(short *) ((char *) self + 0x10);
}

unsigned long func_ov004_02245548(UnkStruct_02245548 *p)
{
    return p->unk_0C;
}

unsigned char func_ov004_02245544(UnkStruct_02245544 *p)
{
    return p->unk_19;
}

short func_ov004_0224553c(void *self)
{
    return *(short *) ((char *) self + 0x12);
}

unsigned long func_ov004_02245538(UnkStruct_02245538 *p)
{
    return p->unk_14;
}

unsigned char func_ov004_02245534(UnkStruct_02245534 *p)
{
    return p->unk_18;
}

void func_ov004_0224551c(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_022454dc((void *) result);
}

void *func_ov004_022454fc(void *self)
{
    func_020ee660(self);
    *(void **) self = (void *) ((int *) data_020da13c);
    *(void **) self = (void *) ((int *) data_ov004_0225672c);
    return self;
}

void *func_ov004_022454dc(void *self)
{
    func_020ee660(self);
    *(void **) self = (void *) ((int *) data_020da13c);
    *(void **) self = (void *) ((int *) data_ov004_0225672c);
    return self;
}

void *func_ov004_022454bc(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) ((int *) data_ov004_0225672c);
    *vp = (int) ((int *) data_020da13c);
    func_020ee62c(p);
    return p;
}

void *func_ov004_02245494(const void **self)
{
    *self = data_ov004_0225672c;
    *self = data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

void *func_ov004_02245474(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) ((int *) data_ov004_0225672c);
    *vp = (int) ((int *) data_020da13c);
    func_020ee62c(p);
    return p;
}
