/* tile_event_3: 11 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02221dd0 @ 0x02221dd0, 0xa8 bytes, Thumb
 * func_ov003_02221da0 @ 0x02221da0, 0x30 bytes, Thumb
 * func_ov003_02221d64 @ 0x02221d64, 0x3c bytes, Thumb
 * func_ov003_02221d3c @ 0x02221d3c, 0x28 bytes, Thumb
 * func_ov003_02221cb4 @ 0x02221cb4, 0x88 bytes, Thumb
 * func_ov003_02221c9c @ 0x02221c9c, 0x18 bytes, Thumb
 * func_ov003_02221c80 @ 0x02221c80, 0x1c bytes, Thumb
 * func_ov003_02221ad8 @ 0x02221ad8, 0x1a8 bytes, Thumb
 * func_ov003_02221a64 @ 0x02221a64, 0x74 bytes, Thumb
 * func_ov003_02221a38 @ 0x02221a38, 0x2c bytes, Thumb
 * func_ov003_02221948 @ 0x02221948, 0xf0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x0a];
    u16 unk_0A;
    u8 pad_0C[0x18 - 0x0c];
    u8 unk_18[1];
    u8 pad_19[0x1c - 0x19];
    int unk_1C;
    u8 pad_20[0x30 - 0x20];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
    u8 pad_40[0x44 - 0x40];
    int unk_44;
    u8 pad_48[0x4c - 0x48];
    s16 unk_4C;
    u8 pad_4E[0x60 - 0x4e];
    u8 unk_60[1];
} UnkStruct_02221dd0;

struct UnkStruct_02221da0;

typedef struct UnkStruct_02221da0_2 {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_02221da0_2;

struct UnkStruct_02221da0 {
    unsigned char pad_00[0x30];
    unsigned int arr[6];
};

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
    char pad_40[4];
    int unk_44;
    char pad_48[6];
    unsigned short unk_4E;
} UnkStruct_02221d64;

typedef struct UnkStruct_02221cb4 {
    char pad_00[0x18];
    int out_x;
    int out_y;
    int out_z;
    char pad_24[0x48 - 0x24];
    unsigned short unk_48;
    char pad_4A[0x50 - 0x4A];
    short unk_50;
    char pad_52[0x54 - 0x52];
    void *unk_54;
} UnkStruct_02221cb4;

typedef struct {
    char pad_00[8];
    u16 unk_08;
    char pad1[6];
    int unk_10, unk_14, unk_18, unk_1C, unk_20;
    char pad_24[0xc];
    int unk_30, unk_34, unk_38;
    char pad_3C[0x10];
    short unk_4C;
    char pad_4E[2];
    short unk_50;
    char pad_52[0x4e];
    unsigned char unk_A0;
} UnkStruct_02221ad8;

typedef struct {
    char pad_00[0x30];
    int unk_30;
    char pad1[8];
    int unk_3C;
} It;

typedef struct {
    fx32 x, y;
} UnkStruct_02221a64;

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[6];
    fx32 unk_10, unk_14;
    char pad_18[0x18];
    fx32 unk_30, unk_34, unk_38, unk_3C, unk_40, unk_44;
} UnkStruct_02221a64_2;

typedef struct {
    char pad_00[4];
    int unk_04;
    unsigned short unk_08;
    char pad_0A[0x60 - 0xa];
    char sub[0x44];
} Elem;

struct Entry {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned short unk_08;
    unsigned char pad_0A[2];
    unsigned int unk_0C;
    unsigned char pad_10[0x18 - 0x10];
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned char pad_24[0x4e - 0x24];
    unsigned short unk_4E;
    unsigned char pad_50[0x60 - 0x50];
    unsigned char data[0xa4 - 0x60];
};

extern void VEC_Add(void *a, void *b, void *c);
extern int func_020044c0(void *a, int b, int c, int d);
extern void func_ov003_02222860(void *a);
extern void func_0204f794(void *addr, unsigned int a, unsigned int b);
extern void func_ov003_02222aa4(struct UnkStruct_02221da0 *self);
extern void func_ov003_02224140(int, int, int, int);
extern short FX_SinCosTable_[];
extern void func_01ffd070(int *out, void **src, int *mat);
extern int data_ov003_0223cf88[3];
extern int func_02034270(void *dst, void *src, int a, int b);
extern void func_0203423c(void *ptr);
extern int func_02090c2c(int a, void *b, int c, void *d);
extern void func_02090aa4(int x, void (*cb)(int *out));
extern void func_020ba31c(int k);
extern void func_020ba334(void);
extern int func_ov003_02219930(void *p);
extern int func_ov003_02220bf0(void *p);
extern int _s32_div_f(int a, int b);
extern int func_020984e8(void);
extern void func_02098ff8(int a, int b);
extern void *data_020e25d4;
extern int func_0204eda8(void *, int, int);
extern int func_02045cec(int *, int);
extern void *func_02045bac(int);
extern void func_0200451c(void *ptr);
extern unsigned int data_020ccf94;
extern int func_02073d90(unsigned int);
extern void func_020044d0(void *, void *);
extern void func_ov003_022226c8(void *);
extern void func_ov003_02222598(void *);
extern void func_ov003_022223bc(void *);
extern void func_ov003_02222318(void *);
extern void func_ov003_022221cc(void *);
extern void func_ov003_022220f4(void *);
extern void func_ov003_02221fb0(void *);
extern void func_ov003_02221f14(void *);

void func_ov003_02221dd0(UnkStruct_02221dd0 *self)
{
    self->unk_3C += 0x19a;
    if (self->unk_3C >= 0x1000) {
        self->unk_3C = 0x1000;
    }
    self->unk_44 = self->unk_3C;
    self->unk_34 -= 0x400;
    VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
    if (self->unk_1C < 0) {
        int flag = 0;
        self->unk_1C = flag;
        self->unk_30 = flag;
        self->unk_34 = flag;
        self->unk_38 = flag;
        if (self->unk_4C == 0) {
            volatile unsigned short val;
            unsigned short a, b;
            val = 0xfff1;
            val = self->unk_0A;
            a = val;
            b = val;
            if (b >= 0x1492 && a <= 0x14fd) {
                flag = 1;
            }
            if (flag != 0) {
                func_020044c0(&self->unk_60, 0x70, 0x7f, 0);
            }
        }
        self->unk_4C = 1;
        func_ov003_02222860(self);
    }
}

void func_ov003_02221da0(struct UnkStruct_02221da0 *self, const UnkStruct_02221da0_2 *data)
{
    func_0204f794((char *) self + 0x18, data->unk_00, data->unk_04);
    self->arr[3] = 0x1000;
    self->arr[4] = 0x1000;
    self->arr[5] = 0x1000;
    self->arr[0] = 0;
    self->arr[1] = 0;
    self->arr[2] = 0;
    func_ov003_02222aa4(self);
}

void func_ov003_02221d64(UnkStruct_02221d64 *s)
{
    unsigned short y = s->unk_4E;
    if ((y >= 6 && y <= 10) || y >= 18) {
        s->unk_3C -= 410;
    }
    if (s->unk_3C <= 0) {
        s->unk_3C = 0;
        func_ov003_02222860((void *) s);
    }
    s->unk_44 = s->unk_3C;
}

void func_ov003_02221d3c(int *r0, int *r1)
{
    int r2 = 0x1000;
    r0[0x3c / 4] = r2;
    r0[0x40 / 4] = r2;
    r0[0x44 / 4] = r2;
    func_ov003_02224140(r1[0], r1[1], 0xfff1, 0);
}

void func_ov003_02221cb4(UnkStruct_02221cb4 *self)
{
    int a, b;
    int mat[3];
    int out[3];

    self->unk_50 += 0x2000;

    a = FX_SinCosTable_[2 * ((unsigned short) self->unk_50 >> 4)] >> 1;
    b = FX_SinCosTable_[2 * ((unsigned short) self->unk_48 >> 4)];

    mat[0] = (a * b) >> 12;
    mat[1] = 0;
    mat[2] = (FX_SinCosTable_[2 * ((unsigned short) self->unk_48 >> 4) + 1] * a) >> 12;

    func_01ffd070(out, &self->unk_54, mat);

    self->out_x = out[0];
    self->out_y = out[1];
    self->out_z = out[2];

    if (self->unk_50 < 0) {
        func_ov003_02222860((void *) self);
    }
}

void func_ov003_02221c9c(int *out)
{
    int *p = out + 1;
    out[1] = data_ov003_0223cf88[0];
    p[1] = data_ov003_0223cf88[1];
    p[2] = data_ov003_0223cf88[2];
}

void func_ov003_02221c80(void *r0, void *r1)
{
    *(unsigned int *) ((char *) r0 + 0x18) = *(unsigned int *) ((char *) r1 + 0);
    *(unsigned int *) ((char *) r0 + 0x1c) = *(unsigned int *) ((char *) r1 + 4);
    *(unsigned int *) ((char *) r0 + 0x20) = *(unsigned int *) ((char *) r1 + 8);
    *(unsigned int *) ((char *) r0 + 0x30) = 0;
    *(unsigned int *) ((char *) r0 + 0x34) = 0xfffff400;
    *(unsigned int *) ((char *) r0 + 0x38) = 0;
}

void func_ov003_02221ad8(UnkStruct_02221ad8 *self)
{
    It it;
    int loc[3];
    int *g;
    int f3c;
    int t;

    func_02034270(&it, &self->unk_18, 0, 0);
    if (it.unk_30 != 0) {
        if (self->unk_4C == 0) {
            VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
            f3c = it.unk_3C;
            if (self->unk_1C < f3c) {
                self->unk_34 = 0;
                g = data_ov003_0223cf88;
                g[0] = self->unk_18;
                g[1] = self->unk_1C;
                g[2] = self->unk_20;
                g[1] = f3c;
                func_02090c2c(0x45, g, 0, &data_020e25d4);
                func_02090c2c(0x4a, data_ov003_0223cf88, 0, &data_020e25d4);
                func_02090aa4(2, func_ov003_02221c9c);
                self->unk_4C = 1;
                self->unk_50 = 0xc;
                self->unk_1C = self->unk_1C - 0x2000;
                func_020ba31c(1);
            }
        } else {
            self->unk_50 = self->unk_50 - 1;
            if (self->unk_50 < 0) {
                func_020ba334();
                func_ov003_02219930(&self->unk_18);
                self->unk_A0 = 0;
                func_ov003_02222860(self);
            }
        }
    } else if (self->unk_4C == 0) {
        VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
        if (self->unk_1C < 0) {
            self->unk_1C = 0;
            self->unk_50 = func_ov003_02220bf0(&self->unk_10);
            func_0204f794((void *) loc, self->unk_10, self->unk_14);
            t = _s32_div_f(loc[2] - self->unk_20, 8);
            self->unk_30 = _s32_div_f(loc[0] - self->unk_18, 8);
            self->unk_34 = 0x1000;
            self->unk_38 = t;
            self->unk_4C = 1;
            func_020ba31c(0);
        }
    } else {
        self->unk_34 = self->unk_34 - 0x400;
        VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
        if (self->unk_1C < 0) {
            self->unk_1C = 0;
            self->unk_30 = 0;
            self->unk_34 = 0;
            self->unk_38 = 0;
            func_020ba334();
            if (self->unk_50 == 0) {
                if (self->unk_08 == 0x137b) {
                    func_02098ff8(func_020984e8(), 0x30);
                }
                func_ov003_02224140(self->unk_10, self->unk_14, self->unk_08, 0);
            }
            self->unk_A0 = 0;
            func_ov003_02222860(self);
        }
    }
    func_0203423c(&it);
}

void func_ov003_02221a64(UnkStruct_02221a64_2 *self, UnkStruct_02221a64 *p, void *c)
{
    int loc[2];
    int h;
    func_0204f794((char *) self + 0x18, p->x, p->y);
    if (func_0204eda8(c, p->x, p->y) == 0) {
        self->unk_08 = 0xfc;
    } else {
        self->unk_08 = 0xfd;
    }
    self->unk_3C = 0x1000;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x1000;
    self->unk_30 = 0;
    self->unk_34 = 0;
    self->unk_38 = 0;
    func_ov003_02224140(p->x, p->y, 0xfff1, 0);
    loc[0] = self->unk_10;
    loc[1] = self->unk_14;
    h = func_02045cec(loc, 0);
    if (h >= 0) {
        *(unsigned short *) ((char *) func_02045bac(h) + 0xa) = 0xfff1;
    }
}

void func_ov003_02221a38(Elem *arr)
{
    int i = 0;
    int value = i;
    unsigned short mask = 0xfff1;

    for (; i < 0x14; i++) {
        char *sub;
        arr->unk_04 = value;
        arr->unk_08 = mask;
        sub = (char *) arr;
        sub += 0x60;
        func_0200451c(sub);
        arr++;
    }
}

void func_ov003_02221948(struct Entry *p)
{
    unsigned short local = 0xfff1;
    unsigned int temp[3];
    unsigned short *plocal;
    unsigned int *ptemp;
    int i;
    func_02073d90(data_020ccf94);
    i = 0;
    plocal = &local;
    ;
    for (; i < 20; p++, i++) {
        if (p->unk_04 == 0) {
            continue;
        }
        p->unk_4E++;
        *plocal = p->unk_08;
        switch (p->unk_0C) {
            case 0:

            case 13:
                func_ov003_022226c8(p);
                break;

            case 1:

            case 2:
                func_ov003_02222598(p);
                break;

            case 3:

            case 14:
                func_ov003_022223bc(p);
                break;

            case 4:
                func_ov003_02222318(p);
                break;

            case 5:
                func_ov003_022221cc(p);
                break;

            case 6:
                func_ov003_022220f4(p);
                break;

            case 7:
                func_ov003_02221fb0(p);
                break;

            case 8:
                func_ov003_02221f14(p);
                break;

            case 9:
                func_ov003_02221dd0((UnkStruct_02221dd0 *) p);
                break;

            case 10:
                func_ov003_02221d64((UnkStruct_02221d64 *) p);
                break;

            case 11:
                func_ov003_02221cb4((UnkStruct_02221cb4 *) p);
                break;

            case 12:
                func_ov003_02221ad8((UnkStruct_02221ad8 *) p);
                break;
        }

        temp[0] = p->unk_18;
        temp[1] = p->unk_1C;
        temp[2] = p->unk_20;
        func_020044d0(p->data, temp);
    }
}
