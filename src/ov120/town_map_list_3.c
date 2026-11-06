/* town_map_list_3: 24 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229b548 @ 0x0229b548, 0xbc bytes, Thumb
 * func_ov120_0229b4b0 @ 0x0229b4b0, 0x98 bytes, Thumb
 * func_ov120_0229b45c @ 0x0229b45c, 0x52 bytes, Thumb
 * func_ov120_0229b434 @ 0x0229b434, 0x26 bytes, Thumb
 * func_ov120_0229b400 @ 0x0229b400, 0x34 bytes, Thumb
 * func_ov120_0229b33c @ 0x0229b33c, 0xc4 bytes, Thumb
 * func_ov120_0229b308 @ 0x0229b308, 0x34 bytes, Thumb
 * func_ov120_0229b2b0 @ 0x0229b2b0, 0x58 bytes, Thumb
 * func_ov120_0229b244 @ 0x0229b244, 0x6a bytes, Thumb
 * func_ov120_0229b22c @ 0x0229b22c, 0x16 bytes, Thumb
 * func_ov120_0229b214 @ 0x0229b214, 0x16 bytes, Thumb
 * func_ov120_0229b1b0 @ 0x0229b1b0, 0x64 bytes, Thumb
 * func_ov120_0229b188 @ 0x0229b188, 0x28 bytes, Thumb
 * func_ov120_0229b168 @ 0x0229b168, 0x1e bytes, Thumb
 * func_ov120_0229b14c @ 0x0229b14c, 0x1a bytes, Thumb
 * func_ov120_0229b100 @ 0x0229b100, 0x4c bytes, Thumb
 * func_ov120_0229b06c @ 0x0229b06c, 0x94 bytes, Thumb
 * func_ov120_0229af10 @ 0x0229af10, 0x15c bytes, Thumb
 * func_ov120_0229aed8 @ 0x0229aed8, 0x38 bytes, Thumb
 * func_ov120_0229ae78 @ 0x0229ae78, 0x60 bytes, Thumb
 * func_ov120_0229adc4 @ 0x0229adc4, 0xb4 bytes, Thumb
 * func_ov120_0229ad5c @ 0x0229ad5c, 0x68 bytes, Thumb
 * func_ov120_0229acf4 @ 0x0229acf4, 0x68 bytes, Thumb
 * func_ov120_0229ac8c @ 0x0229ac8c, 0x68 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229b400_2 {
    char data[0x6C];
} UnkStruct_0229b400_2;

typedef struct UnkStruct_0229b400 {
    char pad_00[0xA0];
    unsigned char count;
    char pad_A1[0x57];
    UnkStruct_0229b400_2 arr[13];
} UnkStruct_0229b400;

struct UnkStruct_0229b1b0 {
    char pad_00[0xa9];
    unsigned char unk_A9;
    char pad_AA[0x720 - 0xaa];
    char sub;
};

struct func_ov120_0229b168_struct {
    unsigned char pad_00[0xa1];
    unsigned char unk_A1;
    unsigned char unk_A2;
};

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
} data_ov118_0229cb40_t;

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char t;
} UnkStruct_0229af10;

typedef struct {
    unsigned char pad_00[0x273a];
    UnkStruct_0229af10 a[3];
    UnkStruct_0229af10 b[14];
} UnkStruct_0229af10_2;

typedef struct {
    short unk_00;
    short unk_02;
} UnkStruct_0229af10_3;

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned char unk_A8;
    unsigned char unk_A9;
} UnkStruct_0229adc4;

typedef struct UnkStruct_0229acf4 {
    unsigned char pad_00[0xa1];
    unsigned char count;
    unsigned char pad_A2[0x2720 - 0xa2];
    unsigned char table[0x100];
} UnkStruct_0229acf4;

extern void MIi_CpuCopy16(void *src, void *dst, int size);
extern void MIi_CpuClear16(unsigned short value, void *dst, int size);
extern void func_ov120_0229a438(void *self, int mode);
extern void func_02070b84(void *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_0209871c(void *, int);
extern int func_020988a4(void *, int);
extern int func_0207cee4(void *, int);
extern u8 data_021dc7bc[];
extern u8 data_021e5a2c[];
extern int func_ov120_0229a448(char *p, int flag);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern void func_02070a04(int a, int b, int c);
extern void func_020a8c1c(void *);
extern int func_ov002_02209018(void *, int);
extern int func_ov002_02208ff8(void *, unsigned);
extern int func_ov002_02208fac(void *, unsigned);
extern int func_0207094c(void *, unsigned);
extern void func_ov120_0229a428(int a, int b);
extern void func_0206fdd4(char *, int, int, int, int, int);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_020896b8(int, void *, int, int, int, int, int);
extern data_ov118_0229cb40_t data_ov120_0229c558;
extern UnkStruct_0229af10_3 *func_ov117_0229a280(void *h, int i);
extern int func_ov117_0229a26c(void *h, int i);
extern const unsigned char data_ov120_0229c500[];
extern void func_ov120_0229a8e8(UnkStruct_0229adc4 *self);
extern void func_ov120_0229a904(UnkStruct_0229adc4 *self);
extern int func_ov120_0229ac60(UnkStruct_0229adc4 *self);
extern void func_ov120_0229ac08(UnkStruct_0229adc4 *self);
extern const unsigned char data_ov120_0229c508[];

unsigned int func_ov120_0229b45c(void *self, unsigned int x, int idx);
void func_ov120_0229b2b0(int arg0, unsigned char *arg1);
void func_ov120_0229b244(int arg1, void *arg2, unsigned arg3);
void func_ov120_0229b1b0(struct UnkStruct_0229b1b0 *self);
char *func_ov120_0229b188(char *p);
unsigned int func_ov120_0229b14c(void *arg0);
unsigned char func_ov120_0229ae78(unsigned char *p, int x, int y);
void func_ov120_0229adc4(UnkStruct_0229adc4 *self, unsigned int idx);
void func_ov120_0229ad5c(int a, int b);
unsigned char func_ov120_0229acf4(UnkStruct_0229acf4 *self, unsigned int key);
unsigned char func_ov120_0229ac8c(int a, unsigned int b);

void func_ov120_0229b548(char *self)
{
    volatile unsigned short buf[4];
    int r4;
    int rows;
    int idx;

    MIi_CpuCopy16(self + 0x1720, self + 0xf20, 0x800);

    rows = (*(unsigned short *) (self + 0x98)) >> 4;
    self[0xa3] = (unsigned char) rows;

    r4 = 0x13;
    for (idx = 0; idx < rows; idx++) {
        buf[0] = 0x10;
        MIi_CpuClear16(buf[0], self + 0xf20 + (r4 << 1), 0x14);
        buf[1] = 0x10;
        MIi_CpuClear16(buf[1], self + 0xf20 + ((r4 + 0x20) << 1), 0x14);
        r4 += 0x40;
    }

    rows += 7;
    r4 = (rows << 6) + 0x13;
    for (idx = rows; idx < 0xd; idx++) {
        buf[2] = 0x10;
        MIi_CpuClear16(buf[2], self + 0xf20 + (r4 << 1), 0x14);
        buf[3] = 0x10;
        MIi_CpuClear16(buf[3], self + 0xf20 + ((r4 + 0x20) << 1), 0x14);
        r4 += 0x40;
    }

    func_ov120_0229a438(self, 2);
}

void func_ov120_0229b4b0(void *self)
{
    unsigned char *lookup;
    int i, v, srcIdx, dstIdx;

    MIi_CpuCopy16((char *) self + 0x1F20, (void *) ((char *) self + 0x1720), 0x800);
    lookup = (unsigned char *) func_ov120_0229b188((char *) self);

    for (i = 0; i < 13; i++) {
        v = func_ov120_0229b45c(self, lookup[i], i);
        srcIdx = v * 64 + 19;
        dstIdx = i * 64 + 19;

        *((unsigned short *) ((char *) self + (dstIdx * 2) + 0x1720)) =
            *((unsigned short *) ((char *) self + (srcIdx * 2) + 0x1F20));
        *((unsigned short *) ((char *) self + ((dstIdx + 1) * 2) + 0x1720)) =
            *((unsigned short *) ((char *) self + ((srcIdx + 1) * 2) + 0x1F20));
        *((unsigned short *) ((char *) self + ((dstIdx + 0x20) * 2) + 0x1720)) =
            *((unsigned short *) ((char *) self + ((srcIdx + 0x20) * 2) + 0x1F20));
        *((unsigned short *) ((char *) self + ((dstIdx + 0x21) * 2) + 0x1720)) =
            *((unsigned short *) ((char *) self + ((srcIdx + 0x21) * 2) + 0x1F20));
    }

    func_ov120_0229a438(self, 2);
}

unsigned int func_ov120_0229b45c(void *self, unsigned int x, int idx)
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

void func_ov120_0229b434(void *arg0)
{
    int i;
    char *p;
    char *q;

    p = (char *) arg0 + 0xa0;
    *p = 0;
    q = (char *) arg0 + 0xf8;

    for (i = 0; i < 13; i++) {
        func_02070b84(q + i * 0x6c);
    }
}

UnkStruct_0229b400_2 *func_ov120_0229b400(UnkStruct_0229b400 *self)
{
    if (self->count >= 13) {
        return (UnkStruct_0229b400_2 *) ((char *) self + 0x608);
    } else {
        self->count++;
        return (UnkStruct_0229b400_2 *) ((char *) self + 0xF8 + (self->count - 1) * sizeof(UnkStruct_0229b400_2));
    }
}

void func_ov120_0229b33c(u8 *self)
{
    int n;
    int i;
    int j;
    int k;
    int cur;

    n = 0;
    cur = func_0209871c(data_021dc7bc, func_02099870((int) func_020984e8()));
    if (cur != -1) {
        self[0x2720] = 1;
        n++;
    }
    for (i = 0; i < 4; i++) {
        if (i != cur && func_020988a4(data_021dc7bc, i) != 0) {
            (self + n)[0x2720] = (u8) (i + 2);
            n++;
        }
    }
    for (i = 0; i < 8; i++) {
        if (func_0207cee4(data_021e5a2c, i) != 0) {
            (self + n)[0x2720] = (u8) (i + 6);
            n++;
        }
    }
    self[0xa1] = (u8) n;
    for (; n < 13; n++) {
        (self + n)[0x272d] = 0;
    }
    k = 0;
    for (j = 0; j < 5; j++) {
        (self + k)[0x272d] = (u8) (j + 0xe);
        k++;
    }
    self[0xa2] = (u8) k;
    for (; k < 13; k++) {
        (self + k)[0x272d] = 0;
    }
}

void func_ov120_0229b308(char *p)
{
    if (func_ov120_0229a448(p, 1) != 0) {
        func_ov120_0229b2b0((int) p, (unsigned char *) (p + 0x272d));
    } else {
        func_ov120_0229b2b0((int) p, (unsigned char *) (p + 0x2720));
    }
}

void func_ov120_0229b2b0(int arg0, unsigned char *arg1)
{
    int i;
    int r;
    int v0 = 0;
    int v1 = 0;

    for (i = 0; i < 13; i++) {
        r = (int) func_ov120_0229b400((UnkStruct_0229b400 *) arg0);
        func_02070adc(r, 6, 0x160 + i * 16, 8, 1, 0xf, v0);
        func_ov120_0229b244(arg0, (void *) r, (unsigned char) arg1[i]);
        func_02070a04(r, v1, v1);
    }
}

void func_ov120_0229b244(int arg1, void *arg2, unsigned arg3)
{
    int t;
    if (arg3 == 0) {
        func_020a8c1c(arg2);
    } else if (arg3 == 1) {
        t = func_02099870((int) func_020984e8());
        func_ov002_02209018(arg2, t);
    } else if (arg3 >= 2 && arg3 < 6) {
        func_ov002_02208ff8(arg2, arg3 - 2);
    } else if (arg3 >= 6 && arg3 < 14) {
        func_ov002_02208fac(arg2, arg3 - 6);
    } else if (arg3 >= 14 && arg3 < 19) {
        func_0207094c(arg2, arg3 + 0x88);
    } else {
        func_020a8c1c(arg2);
    }
}

void func_ov120_0229b22c(int a)
{
    int r4 = a;
    func_ov120_0229a428(r4, 1);
    func_ov120_0229b1b0((struct UnkStruct_0229b1b0 *) r4);
}

void func_ov120_0229b214(int r0)
{
    int r4 = r0;
    func_ov120_0229a438((void *) r4, 1);
    func_ov120_0229b1b0((struct UnkStruct_0229b1b0 *) r4);
}

void func_ov120_0229b1b0(struct UnkStruct_0229b1b0 *self)
{
    int result;
    int flag;

    func_ov120_0229b4b0((void *) self);
    func_ov120_0229b308((char *) self);
    result = (int) func_ov120_0229b14c((void *) self);

    if (result == 0) {
        func_ov120_0229a428((int) self, 8);
        flag = 4;
    } else {
        func_ov120_0229a438((void *) self, 8);
        flag = 3;
    }

    func_0206fdd4(&self->sub, 0x1d, 0xa, 0x1d, 0x15, flag);
    func_ov120_0229a438((void *) self, 0x20);
    func_ov120_0229ad5c((int) self, (unsigned char) self->unk_A9);
}

char *func_ov120_0229b188(char *p)
{
    if (func_ov120_0229a448(p, 1) != 0) {
        return p + 0x272D;
    } else {
        return p + 0x2720;
    }
}

unsigned char func_ov120_0229b168(struct func_ov120_0229b168_struct *self)
{
    if (func_ov120_0229a448((char *) self, 1) != 0) {
        return self->unk_A2;
    } else {
        return self->unk_A1;
    }
}

unsigned int func_ov120_0229b14c(void *arg0)
{
    unsigned int v = (unsigned int) func_ov120_0229b168((struct func_ov120_0229b168_struct *) ((void *) arg0));
    unsigned int result;

    if (v <= 6) {
        result = 0;
    } else {
        result = (v - 6) << 4;
    }

    return result;
}

int func_ov120_0229b100(void *ptr)
{
    unsigned char a = data_021f6c58;
    unsigned char b = data_021f6c54;
    if ((int) a < 0x98 || (int) a > 0xe8) {
        return 0;
    }
    if ((int) b < 0x50 || (int) b >= 0xb0) {
        return 0;
    }
    func_ov120_0229adc4(
        (UnkStruct_0229adc4 *) ptr,
        (unsigned char) ((unsigned char) (((b + (*(unsigned short *) ((char *) ptr + 0x98) - 0x50)) >> 4) + 0xf)));
    return 1;
}

void func_ov120_0229b06c(int unused, int b, int c, int d, int e, int f)
{
    unsigned short mask;

    data_ov120_0229c558.unk_04 = (data_ov120_0229c558.unk_04 & 0xfffffc00) | ((unsigned short) ((d << 1) + 0xc0) & 0x3ff);

    if (e) {
        unsigned short old = data_ov120_0229c558.unk_02;
        mask = (unsigned short) (((unsigned int) old << 18) >> 27 | 8);
        data_ov120_0229c558.unk_02 = (old & 0xffffc1ff) | ((mask & 0x1f) << 9);
    }

    func_020896b8(1, (void *) &data_ov120_0229c558, b, c, f, 1, 0);

    if (e) {
        data_ov120_0229c558.unk_02 =
            (data_ov120_0229c558.unk_02 & 0xffffc1ff) | (((unsigned short) (mask & 0x17) & 0x1f) << 9);
    }
}

void func_ov120_0229af10(UnkStruct_0229af10_2 *d, void *h)
{
    int i;
    int j;
    unsigned int k;
    int m;
    UnkStruct_0229af10_3 *p;

    i = 0;
    for (j = 0; j < 3; j++) {
        p = func_ov117_0229a280(h, i);
        if (p != 0) {
            switch (func_ov117_0229a26c(h, i)) {
                case 0:
                    d->a[j].t = 8;
                    break;
                case 1:
                    d->a[j].t = 7;
                    break;
                case 2:
                    d->a[j].t = 9;
                    break;
                case 3:
                    d->a[j].t = 0x89;
                    break;
                default:
                    d->a[j].t = 0xc;
                    break;
            }
            d->a[j].x = p->unk_00 - 8;
            d->a[j].y = p->unk_02 + 0x10;
        } else {
            d->a[j].t = 0xc;
        }
        i++;
    }
    k = 3;
    for (m = 0; m < 14; m++) {
        p = func_ov117_0229a280(h, k);
        if (p != 0) {
            if (k >= 3 && k <= 0xa) {
                d->b[m].t = 0;
            } else if (k == 0xb) {
                d->b[m].t = 1;
            } else {
                d->b[m].t = *(data_ov120_0229c500 + k - 0xc);
            }
            d->b[m].x = p->unk_00 - 8;
            d->b[m].y = p->unk_02 + 0x10;
        } else {
            d->b[m].t = 0xc;
        }
        k++;
    }
}

int func_ov120_0229aed8(int arg)
{
    int result;

    result = (int) func_ov120_0229ae78((unsigned char *) arg, (unsigned char) data_021f6c58, (unsigned char) data_021f6c54);
    if (result == 14) {
        return 0;
    } else {
        func_ov120_0229adc4((UnkStruct_0229adc4 *) arg, (unsigned char) ((unsigned char) (result + 1)));
        return 1;
    }
}

unsigned char func_ov120_0229ae78(unsigned char *p, int x, int y)
{
    int i;
    unsigned char *q;
    int vx, vy;

    for (i = 0; i < 14; i++) {
        q = p + i * 3;
        if (q[0x2745] == 12) {
            continue;
        }
        vx = q[0x2743];
        if (vx - 8 >= x) {
            continue;
        }
        if (vx + 8 <= x) {
            continue;
        }
        vy = q[0x2744];
        if (vy - 8 >= y) {
            continue;
        }
        if (vy + 8 <= y) {
            continue;
        }
        return i;
    }
    return 14;
}

void func_ov120_0229adc4(UnkStruct_0229adc4 *self, unsigned int idx)
{
    if (idx == 0) {
        self->unk_A8 = 0xe;
        self->unk_A9 = 0xe;
        func_ov120_0229a8e8(self);
        return;
    }
    func_ov120_0229a904(self);
    self->unk_A9 = func_ov120_0229acf4((UnkStruct_0229acf4 *) self, idx);
    self->unk_A8 = func_ov120_0229ac8c((int) self, idx);
    if (idx >= 1 && idx < 0xf) {
        func_ov120_0229a428((int) self, 0x200);
        if (func_ov120_0229a448((char *) self, 1)) {
            if (idx >= 1 && idx <= 9) {
                func_ov120_0229b22c((int) self);
                func_ov120_0229ac60(self);
                return;
            }
        } else {
            if (idx < 1 || idx > 9) {
                func_ov120_0229b214((int) self);
                func_ov120_0229ac60(self);
                return;
            }
        }
    } else {
        func_ov120_0229a438((void *) self, 0x200);
    }
    func_ov120_0229ac08(self);
    func_ov120_0229ad5c((int) self, (unsigned char) 0xe);
    func_ov120_0229ad5c((int) self, (unsigned char) self->unk_A9);
}

void func_ov120_0229ad5c(int a, int b)
{
    func_ov120_0229a438((void *) a, 0x80);
    if (b == 14) {
        func_0206fdd4((char *) (a + 0x1720), 0x13, 0, 0x1c, 0x19, 4);
    } else if (b == 13) {
        func_0206fdd4((char *) (a + 0x1720), 0x13, 0, 0x1c, 7, 3);
    } else {
        int x = b * 2;
        func_0206fdd4((char *) (a + 0x1720), 0x13, x, 0x1c, x + 1, 3);
    }
}

unsigned char func_ov120_0229acf4(UnkStruct_0229acf4 *self, unsigned int key)
{
    if (key == 9) {
        return 13;
    }
    if (key >= 1 && key < 9) {
        unsigned int target = key + 5;
        int i = 0;
        int n = self->count;
        while (i < n) {
            if (self->table[i] == target) {
                return (unsigned char) i;
            }
            i++;
        }
        return 14;
    }
    if (key < 15 && key >= 10) {
        return (unsigned char) (key - 10);
    }
    if (key < 28 && key >= 15) {
        return (unsigned char) (key - 15);
    }
    return 14;
}

unsigned char func_ov120_0229ac8c(int a, unsigned int b)
{
    unsigned char r1;
    const unsigned char *p;
    if (b >= 1 && b < 15) {
        return (unsigned char) (b - 1);
    }
    if (b >= 15 && b < 28) {
        p = (const unsigned char *) func_ov120_0229b188((char *) a);
        r1 = p[b - 15];
        if (r1 == 0) {
            return 14;
        }
        if (r1 == 1 || (r1 >= 2 && r1 < 6)) {
            return 8;
        }
        if (r1 >= 6 && r1 < 14) {
            return (unsigned char) (r1 - 6);
        }
        if (r1 >= 14 && r1 < 19) {
            return data_ov120_0229c508[r1 - 14];
        }
    }
    return 14;
}
