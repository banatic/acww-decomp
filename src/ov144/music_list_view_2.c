/* music_list_view_2: 16 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229a06c @ 0x0229a06c, 0x38 bytes, Thumb
 * func_ov144_0229a040 @ 0x0229a040, 0x2c bytes, Thumb
 * func_ov144_02299f44 @ 0x02299f44, 0xfc bytes, Thumb
 * func_ov144_02299ed4 @ 0x02299ed4, 0x70 bytes, Thumb
 * func_ov144_02299ea8 @ 0x02299ea8, 0x2c bytes, Thumb
 * func_ov144_02299e6c @ 0x02299e6c, 0x3a bytes, Thumb
 * func_ov144_02299df4 @ 0x02299df4, 0x78 bytes, Thumb
 * func_ov144_02299db4 @ 0x02299db4, 0x40 bytes, Thumb
 * func_ov144_02299d3c @ 0x02299d3c, 0x78 bytes, Thumb
 * func_ov144_02299cc4 @ 0x02299cc4, 0x78 bytes, Thumb
 * func_ov144_02299c8c @ 0x02299c8c, 0x38 bytes, Thumb
 * func_ov144_02299c5c @ 0x02299c5c, 0x30 bytes, Thumb
 * func_ov144_02299c2c @ 0x02299c2c, 0x30 bytes, Thumb
 * func_ov144_02299bfc @ 0x02299bfc, 0x30 bytes, Thumb
 * func_ov144_02299b7c @ 0x02299b7c, 0x80 bytes, Thumb
 * func_ov144_02299b48 @ 0x02299b48, 0x32 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xb6];
    s16 unk_B6;
    s16 unk_B8;
    char pad_BA[0x86c - 0xba];
    u16 src[9];
    char pad_87E[0x8f8 - 0x87e];
    u16 arr[9];
} UnkStruct_02299f44;

typedef struct {
    int b[10];
} UnkStruct_02299f44_2;

typedef struct {
    char pad_00[0xA4];
    int unk_A4;
    char pad_A8[0xB8 - (0xA4 + 4)];
    short unk_B8;
    char pad_BA[0xBC - (0xB8 + 2)];
    short unk_BC;
} UnkStruct_02299ea8;

typedef struct {
    char pad_00[0xb6];
    short unk_B6;
    char pad_B8[0x852];
    unsigned char dest[9][128];
    char pad_D8A[0x380];
    unsigned char src[16][128];
} UnkStruct_02299df4;

struct UnkStruct_02299db4 {
    char pad_00[0xB6];
    short unk_B6;
};

struct UnkStruct_02299cc4 {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
};

typedef struct {
    char pad_00[0xba];
    short unk_BA;
    short unk_BC;
} UnkStruct_02299b7c;

typedef struct UnkStruct_02299b48 {
    char pad_00[0xBA];
    short unk_BA;
} UnkStruct_02299b48;

extern void func_02070b84(void *);
extern void *func_02062fbc(UnkStruct_02299f44_2 *c);
extern void func_020a8c1c(void *h);
extern int func_02062ea4(UnkStruct_02299f44_2 *c, u16 *p);
extern void *func_020a8bb8(void *h, UnkStruct_02299f44_2 *c);
extern void func_02070adc(void *h, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *h, int a, int b);
extern void *func_02062f4c(UnkStruct_02299f44_2 *c);
extern int func_ov144_02299680(void *ptr, int arg);
extern int func_020b9bbc(void *dst, void *src, int a, int b, int c);
extern void func_ov144_02299660(void *ptr, int arg);
extern void func_ov144_02299694(UnkStruct_02299ea8 *self, int val);
extern void func_0200284c(int, int, int);
extern void func_ov144_02299670(int, int);
extern void MIi_CpuClear16(int, void *, int);
extern void MIi_CpuCopy16(void *, const void *, int);
extern void func_0206fdd4(void *a, int b, int c, int d, int e, int f);
extern void func_ov144_0229a378(struct UnkStruct_02299cc4 *self);

void func_ov144_02299df4(UnkStruct_02299df4 *self);
void func_ov144_02299d3c(char *ptr);

unsigned char *func_ov144_0229a06c(volatile unsigned char *p)
{
    if (p[0xbf] >= 9) {
        return (unsigned char *) p + 0x69c;
    }
    p[0xbf] = p[0xbf] + 1;
    return (unsigned char *) p + 0x33c + 0x6c * (p[0xbf] - 1);
}

void func_ov144_0229a040(void *arg0)
{
    int i;
    char *p;
    char *base;

    p = (char *) arg0 + 0xbf;
    *p = 0;
    base = (char *) arg0 + 0x33c;
    for (i = 0; i < 9; i++) {
        func_02070b84(base + i * 0x6c);
    }
}

void func_ov144_02299f44(UnkStruct_02299f44 *self)
{
    UnkStruct_02299f44_2 ctx;
    u16 tmp;
    int i;
    void *h;
    int limit;
    int row;
    int col;
    u16 *src;

    func_02062fbc(&ctx);
    row = self->unk_B6;
    if (row < 0) {
        src = self->src;
    } else {
        src = &self->src[row];
    }
    col = (row + 9) % 9;
    limit = self->unk_B8;
    for (i = 0; i < 9; i++) {
        h = 0;
        if (row < 0 || row >= limit) {
            self->arr[col] = 0xfff1;
            h = (void *) func_ov144_0229a06c((volatile unsigned char *) self);
            func_020a8c1c(h);
        } else {
            if (*src != self->arr[col]) {
                self->arr[col] = *src;
                h = (void *) func_ov144_0229a06c((volatile unsigned char *) self);
                tmp = *src;
                func_02062ea4(&ctx, &tmp);
                func_020a8bb8(h, &ctx);
            }
            src++;
        }
        if (h != 0) {
            func_02070adc(h, 4, col * 0x1a + 0x184, 0xd, 0xf, 7, 0);
            func_02070a04(h, 0, 0);
        }
        row++;
        col++;
        if (col >= 9) {
            col = 0;
        }
    }
    func_02062f4c(&ctx);
}

void func_ov144_02299ed4(void *ptr)
{
    if (func_ov144_02299680(ptr, 8) != 0) {
        func_ov144_02299d3c((char *) ptr);
    }
    if (func_ov144_02299680(ptr, 2) != 0) {
        if (func_020b9bbc((char *) ptr + 0x72C, (char *) ptr + 0x190A, 6, 0x800, 0) != 0) {
            func_ov144_02299660(ptr, 2);
        }
    }
    if (func_ov144_02299680(ptr, 4) != 0) {
        func_ov144_02299660(ptr, 4);
        func_ov144_02299f44((UnkStruct_02299f44 *) ptr);
    }
}

void func_ov144_02299ea8(UnkStruct_02299ea8 *self)
{
    self->unk_A4 = (self->unk_B8 - 8) << 4;
    if (self->unk_A4 < 0) {
        self->unk_A4 = 0;
    }
    func_ov144_02299694(self, self->unk_BC);
}

void func_ov144_02299e6c(int *param0, int param1)
{
    int *p;
    int temp;

    p = (int *) ((char *) param0 + 0x9c);
    *p = param1;
    func_0200284c(4, 0, *p - 0x18);
    temp = param1 >> 4;
    *(short *) ((char *) param0 + 0xb6) = (short) temp;
    func_ov144_02299df4((UnkStruct_02299df4 *) ((int) param0));
    func_ov144_02299670((int) param0, 4);
}

void func_ov144_02299df4(UnkStruct_02299df4 *self)
{
    int rem = (self->unk_B6 + 9) % 9;
    int sub = self->unk_B6 & 0xF;
    volatile unsigned short v = 0x10;
    int zero = 0;
    int i;

    MIi_CpuClear16(v, (void *) self->src, 0x800);

    i = 0;
    do {
        MIi_CpuCopy16(&self->dest[rem], &self->src[sub], 0x80);
        rem++;
        if (rem >= 9) {
            rem = zero;
        }
        sub = (sub + 1) & 0xF;
        i++;
    } while (i < 9);

    func_ov144_02299670((int) self, 8);
}

void func_ov144_02299db4(struct UnkStruct_02299db4 *a, int b, int c)
{
    int diff;
    int idx;
    if (b == -1) {
        return;
    }
    diff = b - a->unk_B6;
    if (diff < 0) {
        return;
    }
    if (diff >= 9) {
        return;
    }
    idx = b & 0xF;
    func_0206fdd4((char *) a + 0x110a, 0, idx * 2, 0x1f, idx * 2 + 1, c);
}

void func_ov144_02299d3c(char *ptr)
{
    func_0206fdd4(ptr + 0x110a, 0, 0, 0x1f, 0x1f, 4);
    if (*(short *) (ptr + 0xbc) == *(short *) (ptr + 0xba)) {
        func_ov144_02299db4((struct UnkStruct_02299db4 *) ptr, *(short *) (ptr + 0xbc), 10);
    } else {
        func_ov144_02299db4((struct UnkStruct_02299db4 *) ptr, *(short *) (ptr + 0xbc), 9);
        func_ov144_02299db4((struct UnkStruct_02299db4 *) ptr, *(short *) (ptr + 0xba), 5);
    }
    if (func_020b9bbc(ptr + 0x708, ptr + 0x110a, 4, 0x800, 0) != 0) {
        func_ov144_02299660(ptr, 8);
    }
}

void func_ov144_02299cc4(struct UnkStruct_02299cc4 *self)
{
    if (self->unk_9C != self->unk_A0) {
        if (self->unk_9C > self->unk_A0) {
            self->unk_9C -= 6;
            if (self->unk_9C < self->unk_A0) {
                self->unk_9C = self->unk_A0;
            }
        } else {
            self->unk_9C += 6;
            if (self->unk_9C > self->unk_A0) {
                self->unk_9C = self->unk_A0;
            }
        }
        func_ov144_02299e6c((int *) self, self->unk_9C);
        func_ov144_0229a378(self);
    }
}

void func_ov144_02299c8c(unsigned char *base, unsigned short value)
{
    int idx;
    int k;
    int j;
    int i;

    idx = 0x82;
    for (i = 4; i <= 7; i++) {
        k = idx;
        for (j = 2; j <= 5; j++) {
            *(unsigned short *) (base + 2 * k + 0x190a) = value;
            k++;
            value++;
        }
        idx += 0x20;
    }
}

void func_ov144_02299c5c(int a, int b)
{
    func_ov144_02299670(a, 2);
    func_0206fdd4((void *) (a + 0x190a), 2, 4, 5, 7, b);
}

void func_ov144_02299c2c(void *p, int v)
{
    func_ov144_02299670((int) p, 2);
    func_0206fdd4((char *) p + 0x190a, 2, 0xf, 5, 0x10, v);
}

void func_ov144_02299bfc(int a0, int a1)
{
    func_ov144_02299670(a0, 2);
    func_0206fdd4((void *) (a0 + 0x190a), 2, 12, 5, 13, a1);
}

void func_ov144_02299b7c(UnkStruct_02299b7c *p)
{
    if (p->unk_BA == -1) {
        func_ov144_02299c2c(p, 7);
        if (p->unk_BC == -1) {
            func_ov144_02299c8c((unsigned char *) p, 0x59);
            func_ov144_02299c5c((int) p, 7);
        } else {
            func_ov144_02299c8c((unsigned char *) p, 0x69);
            func_ov144_02299c5c((int) p, 8);
        }
    } else {
        func_ov144_02299c2c(p, 6);
        if (p->unk_BC == -1) {
            func_ov144_02299c8c((unsigned char *) p, 0x59);
            func_ov144_02299c5c((int) p, 6);
        } else {
            func_ov144_02299c8c((unsigned char *) p, 0x69);
            func_ov144_02299c5c((int) p, 8);
        }
    }
}

int func_ov144_02299b48(UnkStruct_02299b48 *self, int value)
{
    int changed = (self->unk_BA != value);
    self->unk_BA = value;
    func_ov144_02299670((int) self, 8);
    func_ov144_02299b7c((UnkStruct_02299b7c *) self);
    return changed;
}
