/* map_menu_list_6: 15 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229b778 @ 0x0229b778, 0xbc bytes, Thumb
 * func_ov118_0229b6e0 @ 0x0229b6e0, 0x98 bytes, Thumb
 * func_ov118_0229b68c @ 0x0229b68c, 0x52 bytes, Thumb
 * func_ov118_0229b664 @ 0x0229b664, 0x26 bytes, Thumb
 * func_ov118_0229b630 @ 0x0229b630, 0x34 bytes, Thumb
 * func_ov118_0229b564 @ 0x0229b564, 0xcc bytes, Thumb
 * func_ov118_0229b530 @ 0x0229b530, 0x34 bytes, Thumb
 * func_ov118_0229b4d8 @ 0x0229b4d8, 0x58 bytes, Thumb
 * func_ov118_0229b46c @ 0x0229b46c, 0x6a bytes, Thumb
 * func_ov118_0229b454 @ 0x0229b454, 0x16 bytes, Thumb
 * func_ov118_0229b43c @ 0x0229b43c, 0x16 bytes, Thumb
 * func_ov118_0229b3d8 @ 0x0229b3d8, 0x64 bytes, Thumb
 * func_ov118_0229b3b0 @ 0x0229b3b0, 0x28 bytes, Thumb
 * func_ov118_0229b390 @ 0x0229b390, 0x1e bytes, Thumb
 * func_ov118_0229b374 @ 0x0229b374, 0x1a bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229b630 {
    unsigned char pad_00[0xa0];
    unsigned char count;
} UnkStruct_0229b630;

struct UnkStruct_0229b3d8 {
    char pad_00[0xaa];
    unsigned char byte_a9;
    char pad_AB[0x723 - 0xaa];
    char sub;
};

typedef struct {
    char pad_00[0xa1];
    unsigned char a1;
    unsigned char a2;
} UnkStruct_0229b390;

extern void MIi_CpuCopy16(void *src, void *dst, int size);
extern void MIi_CpuClear16(unsigned short value, void *dst, int size);
extern void func_ov118_0229a450(void *self, int mode);
extern void func_02070b84(void *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_0209871c(void *, int);
extern int func_020988a4(void *, int);
extern int func_0207cee4(void *, int);
extern u8 data_021dc7bc[];
extern u8 data_021e5a2c[];
extern int func_ov118_0229a460(void *p, int flag);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);
extern void func_020a8c1c(int);
extern int func_ov002_02209018(int, int);
extern int func_ov002_02208ff8(int, int);
extern int func_ov002_02208fac(int, int);
extern int func_0207094c(int, int);
extern void func_ov118_0229a440(int, int);
extern void func_0206fdd4(char *, int, int, int, int, int);
extern void func_ov118_0229af64(struct UnkStruct_0229b3d8 *, unsigned char);

unsigned int func_ov118_0229b68c(void *self, unsigned int x, int idx);
void func_ov118_0229b4d8(void *p, unsigned char *q);
void func_ov118_0229b46c(int a, int b, unsigned int c);
void func_ov118_0229b3d8(struct UnkStruct_0229b3d8 *self);
int func_ov118_0229b3b0(int a);
unsigned int func_ov118_0229b374(void *arg0);

void func_ov118_0229b778(char *self)
{
    volatile unsigned short buf[4];
    int r4;
    int rows;
    int idx;

    MIi_CpuCopy16(self + 0x1724, self + 0xf24, 0x800);

    rows = (*(unsigned short *) (self + 0x98)) >> 4;
    self[0xa3] = (unsigned char) rows;

    r4 = 0x13;
    for (idx = 0; idx < rows; idx++) {
        buf[0] = 0x10;
        MIi_CpuClear16(buf[0], self + 0xf24 + (r4 << 1), 0x14);
        buf[1] = 0x10;
        MIi_CpuClear16(buf[1], self + 0xf24 + ((r4 + 0x20) << 1), 0x14);
        r4 += 0x40;
    }

    rows += 7;
    r4 = (rows << 6) + 0x13;
    for (idx = rows; idx < 0xd; idx++) {
        buf[2] = 0x10;
        MIi_CpuClear16(buf[2], self + 0xf24 + (r4 << 1), 0x14);
        buf[3] = 0x10;
        MIi_CpuClear16(buf[3], self + 0xf24 + ((r4 + 0x20) << 1), 0x14);
        r4 += 0x40;
    }

    func_ov118_0229a450(self, 2);
}

void func_ov118_0229b6e0(char *base)
{
    int i;
    int srcIdx, dstIdx;
    unsigned char *saved;

    MIi_CpuCopy16(base + 0x1f24, base + 0x1724, 0x800);
    saved = (unsigned char *) func_ov118_0229b3b0((int) base);

    for (i = 0; i < 13; i++) {
        srcIdx = (func_ov118_0229b68c(base, saved[i], i) << 6) + 0x13;
        dstIdx = (i << 6) + 0x13;

        *(unsigned short *) (base + (dstIdx * 2) + 0x1724) = *(unsigned short *) (base + (srcIdx * 2) + 0x1f24);
        *(unsigned short *) (base + ((dstIdx + 1) * 2) + 0x1724) = *(unsigned short *) (base + ((srcIdx + 1) * 2) + 0x1f24);
        *(unsigned short *) (base + ((dstIdx + 0x20) * 2) + 0x1724) =
            *(unsigned short *) (base + ((srcIdx + 0x20) * 2) + 0x1f24);
        *(unsigned short *) (base + ((dstIdx + 0x21) * 2) + 0x1724) =
            *(unsigned short *) (base + ((srcIdx + 0x21) * 2) + 0x1f24);
    }

    func_ov118_0229a450(base, 2);
}

unsigned int func_ov118_0229b68c(void *self, unsigned int x, int idx)
{
    if (x == 0) {
        return 7;
    }
    if (x < 6) {
        return 0;
    }
    if (x >= 6 && x < 14) {
        return 1;
    }
    switch (x - 14) {
        case 2:
            return 2;
        case 0:
            return 3;
        case 3:
            return 4;
        case 1:
            return 5;
        case 4:
            return 6;
        default:
            return 7;
    }
}

void func_ov118_0229b664(void *arg0)
{
    int i;
    char *p;
    char *q;

    p = (char *) arg0 + 0xa0;
    *p = 0;
    q = (char *) arg0 + 0xfc;
    for (i = 0; i < 13; i++) {
        func_02070b84(q + i * 0x6c);
    }
}

char *func_ov118_0229b630(UnkStruct_0229b630 *p)
{
    if (p->count >= 13) {
        return (char *) p + 0x60c;
    }
    p->count++;
    return (char *) p + 0xfc + 0x6c * (p->count - 1);
}

void func_ov118_0229b564(u8 *self)
{
    int n;
    int i;
    int j;
    int k;
    int cur;

    n = 0;
    cur = func_0209871c(data_021dc7bc, func_02099870((int) func_020984e8()));
    if (cur != -1) {
        self[0x478a] = 1;
        n++;
    }
    for (i = 0; i < 4; i++) {
        if (i != cur && func_020988a4(data_021dc7bc, i) != 0) {
            (self + n)[0x478a] = (u8) (i + 2);
            n++;
        }
    }
    self[0xb0] = (u8) n;
    for (i = 0; i < 8; i++) {
        if (func_0207cee4(data_021e5a2c, i) != 0) {
            (self + n)[0x478a] = (u8) (i + 6);
            n++;
        }
    }
    self[0xa1] = (u8) n;
    for (; n < 13; n++) {
        (self + n)[0x4797] = 0;
    }
    k = 0;
    for (j = 0; j < 5; j++) {
        (self + k)[0x4797] = (u8) (j + 0xe);
        k++;
    }
    self[0xa2] = (u8) k;
    for (; k < 13; k++) {
        (self + k)[0x4797] = 0;
    }
}

void func_ov118_0229b530(void *p)
{
    if (func_ov118_0229a460(p, 1)) {
        func_ov118_0229b4d8(p, (unsigned char *) ((char *) p + 0x4797));
    } else {
        func_ov118_0229b4d8(p, (unsigned char *) ((char *) p + 0x478a));
    }
}

void func_ov118_0229b4d8(void *p, unsigned char *q)
{
    int x = 0;
    int y = 0;
    int i;
    for (i = 0; i < 13; i++) {
        int r = (int) func_ov118_0229b630((UnkStruct_0229b630 *) p);
        func_02070adc(r, 6, 0x160 + i * 16, 8, 1, 0xf, x);
        func_ov118_0229b46c((int) p, r, (unsigned char) q[i]);
        func_02070a04(r, y, y);
    }
}

void func_ov118_0229b46c(int a, int b, unsigned int c)
{
    if (c == 0) {
        func_020a8c1c(b);
    } else if (c == 1) {
        func_ov002_02209018(b, func_02099870(func_020984e8()));
    } else if (c >= 2 && c < 6) {
        func_ov002_02208ff8(b, c - 2);
    } else if (c >= 6 && c < 14) {
        func_ov002_02208fac(b, c - 6);
    } else if (c >= 14 && c < 19) {
        func_0207094c(b, c + 0x88);
    } else {
        func_020a8c1c(b);
    }
}

void func_ov118_0229b454(int r0)
{
    int r4 = r0;
    func_ov118_0229a440(r4, 1);
    func_ov118_0229b3d8((struct UnkStruct_0229b3d8 *) r4);
}

void func_ov118_0229b43c(int a)
{
    func_ov118_0229a450((void *) a, 1);
    func_ov118_0229b3d8((struct UnkStruct_0229b3d8 *) a);
}

void func_ov118_0229b3d8(struct UnkStruct_0229b3d8 *self)
{
    int result;
    int flag;

    func_ov118_0229b6e0((char *) self);
    func_ov118_0229b530((void *) self);
    result = (int) func_ov118_0229b374((void *) self);

    if (result == 0) {
        func_ov118_0229a440((int) self, 8);
        flag = 4;
    } else {
        func_ov118_0229a450((void *) self, 8);
        flag = 3;
    }

    func_0206fdd4(&self->sub, 0x1d, 0xa, 0x1d, 0x15, flag);
    func_ov118_0229a450((void *) self, 0x20);
    func_ov118_0229af64(self, self->byte_a9);
}

int func_ov118_0229b3b0(int a)
{
    int result;
    if (func_ov118_0229a460((void *) a, 1)) {
        result = a + 0x4797;
    } else {
        result = a + 0x478a;
    }
    return result;
}

unsigned char func_ov118_0229b390(UnkStruct_0229b390 *p)
{
    if (func_ov118_0229a460((void *) p, 1)) {
        return p->a2;
    } else {
        return p->a1;
    }
}

unsigned int func_ov118_0229b374(void *arg0)
{
    unsigned int t;

    t = (unsigned int) func_ov118_0229b390((UnkStruct_0229b390 *) ((void *) arg0));
    if (t <= 6) {
        return 0;
    } else {
        return (t - 6) << 4;
    }
}
