/* music_player_2: 13 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022163f4 @ 0x022163f4, 0x4 bytes, Thumb
 * func_ov004_022163f0 @ 0x022163f0, 0x2 bytes, Thumb
 * func_ov004_022163ec @ 0x022163ec, 0x4 bytes, Thumb
 * func_ov004_022163e0 @ 0x022163e0, 0xc bytes, Thumb
 * func_ov004_022163c4 @ 0x022163c4, 0x1a bytes, Thumb
 * func_ov004_02216360 @ 0x02216360, 0x64 bytes, Thumb
 * func_ov004_0221635c @ 0x0221635c, 0x4 bytes, Thumb
 * func_ov004_02216350 @ 0x02216350, 0xc bytes, Thumb
 * func_ov004_0221626c @ 0x0221626c, 0xe4 bytes, Thumb
 * func_ov004_02216248 @ 0x02216248, 0x24 bytes, Thumb
 * func_ov004_02216244 @ 0x02216244, 0x4 bytes, Thumb
 * func_ov004_02216214 @ 0x02216214, 0x30 bytes, Thumb
 * func_ov004_02216200 @ 0x02216200, 0x14 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0221626c {
    int d[10];
};

typedef struct UnkStruct_0221626c_2 {
    char pad_00[8];
    unsigned int unk_08;
} UnkStruct_0221626c_2;

typedef struct Main {
    char pad_00[0xec];
    char sub[0x1e];
    u8 unk_10A;
    char pad_10B[0x21];
    UnkStruct_0221626c_2 *unk_12C;
} Main;

struct UnkStruct_02216248;

struct UnkStruct_02216248_2;

struct UnkStruct_02216248 {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_02216248_2 {
    char pad_00[300];
    struct UnkStruct_02216248 *b;
};

struct UnkStruct_02216214 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_02216214_2 {
    char pad_00[0xec];
    char unk_EC[0x40];
    struct UnkStruct_02216214 *unk_12C;
};

extern int func_ov004_022164a0(int a, int b);
extern int func_0206fbf8(int k);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern u16 func_0206f668(void);
extern int func_0205265c(void *self, int a, u8 b, int c);
extern int func_0203e020(void *self);
extern void func_0203ee14(void *self, void *p);
extern void func_020a8164(void *p, void *d);
extern void *data_ov004_022531f0;
extern int func_020b6680(void);
extern int func_020b66b0(void);
extern int func_0207cec0(void *d, int a);
extern unsigned int func_0207f2c4(int result);
extern void *func_02062f90(struct UnkStruct_0221626c *o, u16 *p);
extern void func_020683b4(void *h, int a, struct UnkStruct_0221626c *o, int k);
extern void *func_02062f4c(struct UnkStruct_0221626c *o);
extern u16 *func_02060b70(void);
extern int data_021e5a2c;
extern void func_0203ee08(struct UnkStruct_02216214_2 *obj, char *ptr);
extern const u8 data_ov004_02247660[];

int func_ov004_022163f4(void *callbackObject)
{
    return 1;
}

void func_ov004_022163f0(void *callbackObject) {}

int func_ov004_022163ec(void *callbackObject)
{
    return 1;
}

void func_ov004_022163e0(int a)
{
    func_ov004_022164a0(a, 2);
}

int func_ov004_022163c4(void *callbackObject)
{
    if (func_0206fbf8(0x40) != 0) {
        return 1;
    }
    return 0;
}

void func_ov004_02216360(void *self)
{
    volatile u16 t;
    int ok;
    u16 v;
    int k;

    if (func_0206fbc0()) {
        if (func_0206fc6c()) {
            t = func_0206f668();
            ok = 0;
            v = t;
            if (v >= 0x1323 && v <= 0x1368) {
                ok = 1;
            }
            if (ok) {
                k = v - 0x1323;
            } else {
                k = -1;
            }
            func_0205265c(self, 1, (u8) k, 1);
        }
        func_0203e020(self);
    }
}

int func_ov004_0221635c(void *callbackObject)
{
    return 1;
}

void func_ov004_02216350(int a)
{
    func_ov004_022164a0(a, 4);
}

int func_ov004_0221626c(Main *self)
{
    u16 tv[4];
    struct UnkStruct_0221626c a;
    struct UnkStruct_0221626c b;
    void *p;
    unsigned int n;
    int m;
    u16 v;
    u16 *q;

    p = self;
    if (self != 0) {
        p = (char *) self + 0xec;
    }
    func_0203ee14(self, p);
    self->unk_12C->unk_08 = 1;
    func_020a8164((char *) self + 0xec, &data_ov004_022531f0);
    if (func_020b6680() != 0) {
        n = 0;
        if ((m = func_0207cec0(&data_021e5a2c, func_020b66b0())) != 0) {
            n = func_0207f2c4(m);
        }
        tv[2] = (n < 0x46) ? (u16) (n + 0x1323) : (u16) 0x1323;
        func_02062f90(&a, &tv[2]);
        self->unk_10A = 5;
        func_020683b4(self->unk_12C, 0, &a, 7);
        func_02062f4c(&a);
    } else {
        q = func_02060b70();
        m = 0;
        v = *q;
        if (v >= 0x1323 && v <= 0x1368) {
            m = 1;
        }
        if (m != 0) {
            func_02062f90(&b, q);
            self->unk_10A = 5;
            func_020683b4(self->unk_12C, 0, &b, 7);
            func_02062f4c(&b);
        } else {
            self->unk_10A = 6;
        }
    }
    return 1;
}

void func_ov004_02216248(struct UnkStruct_02216248_2 *self)
{
    struct UnkStruct_02216248 *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_022164a0((int) self, 5);
        }
    }
}

int func_ov004_02216244(void *callbackObject)
{
    return 1;
}

void func_ov004_02216214(struct UnkStruct_02216214_2 *obj)
{
    if (obj->unk_12C && obj->unk_12C->unk_04 == 0) {
        char *p = (char *) obj;
        if (p) {
            p += 0xec;
        }
        func_0203ee08(obj, p);
        func_0203e020((void *) obj);
    }
}

u8 func_ov004_02216200(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_02247660[i];
    }
    return 0;
}
