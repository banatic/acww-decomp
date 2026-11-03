/* bromide: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02213500 @ 0x02213500, 0x4 bytes, Thumb
 * func_ov004_022134dc @ 0x022134dc, 0x24 bytes, Thumb
 * func_ov004_022134d8 @ 0x022134d8, 0x4 bytes, Thumb
 * func_ov004_022134cc @ 0x022134cc, 0xc bytes, Thumb
 * func_ov004_02213450 @ 0x02213450, 0x7c bytes, Thumb
 * func_ov004_0221342c @ 0x0221342c, 0x24 bytes, Thumb
 * func_ov004_02213428 @ 0x02213428, 0x4 bytes, Thumb
 * func_ov004_022133f8 @ 0x022133f8, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02213450 {
    char pad_00[8];
    unsigned int unk_08;
} UnkStruct_02213450;

typedef struct Main {
    char pad_00[0xec];
    char sub[0x1e];
    signed char unk_10A;
    char pad_10B[0x21];
    UnkStruct_02213450 *unk_12C;
} Main;

struct UnkStruct_0221342c;

struct UnkStruct_0221342c_2;

struct UnkStruct_0221342c {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_0221342c_2 {
    char pad_00[300];
    struct UnkStruct_0221342c *b;
};

struct UnkStruct_022133f8 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_022133f8_2 {
    char pad_00[0xec];
    char unk_EC[0x40];
    struct UnkStruct_022133f8 *unk_12C;
};

extern int func_0203e0a8(int argument0, int argument1);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_02213590(int a, int b);
extern void func_0203ee14(void *self, void *ptr);
extern void func_020a8164(void *ptr, void *data);
extern void *func_ov004_0220fde0(void *self);
extern int func_0204bc50(void *p, int a);
extern void *data_ov004_022531b0;
extern void func_0203ee08(struct UnkStruct_022133f8_2 *obj, char *ptr);
extern int func_0203e020(struct UnkStruct_022133f8_2 *obj);

int func_ov004_02213500(void *callbackObject)
{
    return 1;
}

int func_ov004_022134dc(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0220d2a8(self + 0x740);
    if (v1 != 0x0) {
        return func_0203e0a8((int) (self), (int) (0x0));
    }
    return v1;
}

int func_ov004_022134d8(void *callbackObject)
{
    return 1;
}

void func_ov004_022134cc(int a)
{
    func_ov004_02213590(a, 2);
}

int func_ov004_02213450(Main *self)
{
    void *p;
    volatile u16 vv[2];
    int m;
    u16 t;
    int r;

    p = self;
    if (self != 0) {
        p = (char *) self + 0xec;
    }
    func_0203ee14(self, p);
    self->unk_12C->unk_08 = 1;
    vv[1] = (u16) func_0204bc50(func_ov004_0220fde0(self), 0);
    m = 0;
    t = vv[1];
    if (t >= 0x47d8 && t <= 0x4a47) {
        m = 1;
    }
    if (m != 0) {
        r = (t - 0x47d8) >> 2;
    } else {
        r = -1;
    }
    func_020a8164((char *) self + 0xec, &data_ov004_022531b0);
    self->unk_10A = (signed char) r;
    return 1;
}

void func_ov004_0221342c(struct UnkStruct_0221342c_2 *self)
{
    struct UnkStruct_0221342c *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_02213590((int) self, 3);
        }
    }
}

int func_ov004_02213428(void *callbackObject)
{
    return 1;
}

void func_ov004_022133f8(struct UnkStruct_022133f8_2 *obj)
{
    if (obj->unk_12C && obj->unk_12C->unk_04 == 0) {
        char *p = (char *) obj;
        if (p) {
            p += 0xec;
        }
        func_0203ee08(obj, p);
        func_0203e020(obj);
    }
}
