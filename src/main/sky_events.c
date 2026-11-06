/* sky_events: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bd2d0 @ 0x020bd2d0, 0xe4 bytes, Thumb
 * func_020bd1c4 @ 0x020bd1c4, 0x10c bytes, Thumb
 * func_020bd124 @ 0x020bd124, 0xa0 bytes, Thumb
 * func_020bd054 @ 0x020bd054, 0xd0 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_020bd2d0 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
} UnkStruct_020bd2d0;

typedef struct UnkStruct_020bd2d0_2 {
    unsigned char pad_00[0x1464];
    unsigned int unk_1464;
    unsigned char pad_1468[0x2eb8 - 0x1468];
    unsigned char pad_2EB8[0x2f18 - 0x2eb8];
    unsigned char unk_2F18;
    unsigned char unk_2F19;
    unsigned char unk_2F1A;
    unsigned char pad_2F1B[0x2f24 - 0x2f1b];
    unsigned char unk_2F24;
} UnkStruct_020bd2d0_2;

struct UnkStruct_020bd1c4 {
    u8 pad_00[0x1464];
    int unk_1464;
    u8 pad_1468[0x2f18 - 0x1468];
    u8 unk_2F18;
    u8 pad_2F19[1];
    u8 unk_2F1A;
    u8 pad_2F1B[0x2f25 - 0x2f1b];
    u8 unk_2F25;
    u8 unk_2F26;
};

struct UnkStruct_020bd1c4_2 {
    int x;
    int y;
};

struct UnkStruct_020bd1c4_3 {
    u8 pad_00[0x64];
    int unk_64;
};

typedef struct {
    u8 pad_00[0x64];
    u32 unk_64;
} UnkStruct_020bd124_2;

typedef struct {
    u8 pad_00[0x1464];
    u32 unk_1464;
    u8 pad_1468[0x2f19 - 0x1468];
    u8 unk_2F19;
    u8 pad_2F1A;
    u8 unk_2F1B;
    u8 pad_2F1C[0x2f27 - 0x2f1c];
    u8 unk_2F27;
} UnkStruct_020bd124;

typedef struct {
    unsigned char pad_00[0xe80];
    unsigned int unk_E80;
    unsigned char pad_E84[0x2094];
    unsigned char unk_2F18;
    unsigned char unk_2F19;
    unsigned char pad_2F1A[0x37];
    unsigned char unk_2F51;
} UnkStruct_020bd054;

extern UnkStruct_020bd2d0 *data_020ccf94;
extern int func_02073dd4(UnkStruct_020bd2d0 *a, unsigned int b);
extern int func_020644cc(int a);
extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_020be9dc(void);
extern void *func_020bdc50(void *a, int b, int c, int d, int e);
extern void func_020bece0(void *a);
extern int data_021dc7a8[];
extern int func_0209f150(void *, int);
extern void func_0209e474(struct UnkStruct_020bd1c4_2 *);
extern void MI_CpuCopy8(struct UnkStruct_020bd1c4_2 *, struct UnkStruct_020bd1c4_2 *, u32);
extern int func_0203fc78(int, struct UnkStruct_020bd1c4_2 *, int);
extern int func_0208602c(void);
extern int func_020860bc(int);
extern int func_02087b1c(void *);
extern u32 func_02082644(u32);
extern u32 func_0201bea4(u32);
extern u32 func_020ba4e4(void);
extern int func_020860c0(int);
extern u32 func_02087e0c(void *);
extern unsigned char data_021f3b28[4];
extern unsigned char data_020d22b5[];
extern void func_020bc548(UnkStruct_020bd054 *self);
extern void func_020bdc14(UnkStruct_020bd054 *self, int a);

// placeholder, will be removed
void func_020bd2d0(UnkStruct_020bd2d0_2 *self)
{
    int r0, r5;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }
    if (self->unk_2F19 < 10 || self->unk_2F19 >= 16) {
        return;
    }
    if (self->unk_2F1A == self->unk_2F18) {
        return;
    }
    if ((unsigned int) self->unk_2F18 % 10 != 4) {
        return;
    }
    if (self->unk_1464 == 5) {
        return;
    }
    if (self->unk_2F24 == 0) {
        self->unk_2F24 = func_020644cc(8) + 1;
    }
    r5 = self->unk_2F24;
    r0 = func_020644cc(8);
    if (r0 < r5) {
        if (func_02099020(func_020984e8(), 0x30) == 0 && func_020be9dc() != 0 && func_020644cc(4) == 0) {
            func_020bdc50(self, 5, 0x2d, 0, 1);
        } else {
            func_020bdc50(self, 5, 0x2d, 0, 0);
            func_020bece0((char *) self + 0x2eb8);
        }
        self->unk_2F24 = 1;
    } else {
        if ((unsigned int) r5 < 8) {
            self->unk_2F24 = self->unk_2F24 + 1;
        }
    }
}

void func_020bd1c4(struct UnkStruct_020bd1c4 *p)
{
    struct UnkStruct_020bd1c4_2 a;
    struct UnkStruct_020bd1c4_2 b;
    int t;
    int v;
    int rem;
    int c;

    if (p->unk_2F26) {
        if (func_0209f150(data_021dc7a8, 9)) {
            p->unk_2F26 = 0;
        } else {
            a.x = 0;
            a.y = 0;
            func_0209e474(&a);
            MI_CpuCopy8(&a, &b, 8);
            t = func_0203fc78(0x44, &b, 0) ? 0 : 1;
            if (t) {
                p->unk_2F26 = 0;
            }
        }
    }
    if (p->unk_2F26) {
        if (func_02073dd4((UnkStruct_020bd2d0 *) ((*(struct UnkStruct_020bd1c4_3 **) &data_020ccf94)),
                          (*(struct UnkStruct_020bd1c4_3 **) &data_020ccf94)->unk_64) == 0) {
            v = p->unk_2F18;
            rem = (unsigned int) v % 10;
            if (p->unk_2F1A != v) {
                if (rem == 2 || rem == 7) {
                    if (func_02087b1c((void *) func_020860bc((int) func_0208602c())) == 0) {
                        if (p->unk_1464 != 6) {
                            if (p->unk_2F25 == 0) {
                                p->unk_2F25 = func_020644cc(8) + 1;
                            }
                            c = p->unk_2F25;
                            if (func_020644cc(8) < c) {
                                func_020bdc50((void *) p, 6, 0x2d, 0, 0);
                                p->unk_2F25 = 1;
                            } else if (c < 8U) {
                                p->unk_2F25++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void func_020bd124(UnkStruct_020bd124 *p)
{
    u32 r;
    u32 v;
    u8 b1, b2;

    if (p->unk_2F27) {
        r = func_02082644(8);
        if (r) {
            if (func_0201bea4(r)) {
                p->unk_2F27 = 0;
            }
        }
    }

    if (p->unk_2F27 == 0) {
        return;
    }

    if ((u32) func_02073dd4((UnkStruct_020bd2d0 *) ((*(UnkStruct_020bd124_2 **) &data_020ccf94)),
                            (*(UnkStruct_020bd124_2 **) &data_020ccf94)->unk_64) != 0) {
        return;
    }

    v = func_020ba4e4();
    if (v == 1) {
        return;
    }
    if (v == 2) {
        return;
    }

    b1 = p->unk_2F19;
    b2 = p->unk_2F1B;
    if (b1 == b2) {
        return;
    }
    if (b1 != 9 && b1 != 0x11) {
        return;
    }

    if (func_02087e0c((void *) func_020860c0((int) func_0208602c())) != 0) {
        return;
    }

    if (p->unk_1464 == 7) {
        return;
    }

    func_020bdc50((void *) p, 7, 0x2d, 0, 0);
}

void func_020bd054(UnkStruct_020bd054 *self)
{
    unsigned char v;
    unsigned char t, t2, t3;
    int r1;
    int f4;

    self->unk_2F51 = 0;
    v = data_021f3b28[2];
    if (v >= 0x13 && v <= 0x17) {
        t = data_020d22b5[v];
        t2 = self->unk_2F19;
        if (t == t2) {
            t3 = self->unk_2F18;
            if ((int) t3 < 0x2d) {
                if ((int) t3 <= 0xf) {
                    r1 = t3 * 0xccc;
                } else {
                    r1 = (t3 - 0xf) * (int) 0xfffff99a;
                    r1 = r1 + 0xc000;
                }
                if (r1 < 0) {
                    r1 = 0;
                } else if (r1 > 0xc000) {
                    r1 = 0xc000;
                }
                r1 = (r1 + 0x800) >> 12;
                self->unk_2F51 = (unsigned char) r1;
            }
        }
    }

    f4 = (self->unk_E80 == 10) ? 1 : 0;
    if (self->unk_2F51 != 0) {
        func_020bc548(self);
        if (f4 == 0) {
            if ((int) func_020bdc50((void *) self, 10, 0x20, 0, 0) == 0) {
                self->unk_2F51 = 0;
            }
        }
    } else {
        if (f4 != 0) {
            func_020bdc14(self, 10);
        }
    }
}
