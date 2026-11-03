/* sky_4: 29 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bb99c @ 0x020bb99c, 0x78 bytes, Thumb
 * func_020bb998 @ 0x020bb998, 0x2 bytes, Thumb
 * func_020bb8e0 @ 0x020bb8e0, 0xb8 bytes, Thumb
 * func_020bb89c @ 0x020bb89c, 0x44 bytes, Thumb
 * func_020bb830 @ 0x020bb830, 0x6c bytes, Thumb
 * func_020bb7e0 @ 0x020bb7e0, 0x50 bytes, Thumb
 * func_020bb7a0 @ 0x020bb7a0, 0x40 bytes, Thumb
 * func_020bb75c @ 0x020bb75c, 0x44 bytes, Thumb
 * func_020bb6d8 @ 0x020bb6d8, 0x84 bytes, Thumb
 * func_020bb6b0 @ 0x020bb6b0, 0x28 bytes, Thumb
 * func_020bb6a0 @ 0x020bb6a0, 0x10 bytes, Thumb
 * func_020bb66c @ 0x020bb66c, 0x34 bytes, Thumb
 * func_020bb608 @ 0x020bb608, 0x64 bytes, Thumb
 * func_020bb568 @ 0x020bb568, 0xa0 bytes, Thumb
 * func_020bb4e0 @ 0x020bb4e0, 0x88 bytes, Thumb
 * func_020bb480 @ 0x020bb480, 0x60 bytes, Thumb
 * func_020bb3f4 @ 0x020bb3f4, 0x8c bytes, Thumb
 * func_020bb3a4 @ 0x020bb3a4, 0x50 bytes, Thumb
 * func_020bb35c @ 0x020bb35c, 0x48 bytes, Thumb
 * func_020bb30c @ 0x020bb30c, 0x50 bytes, Thumb
 * func_020bb2ec @ 0x020bb2ec, 0x20 bytes, Thumb
 * func_020bb290 @ 0x020bb290, 0x5c bytes, Thumb
 * func_020bb240 @ 0x020bb240, 0x50 bytes, Thumb
 * func_020bb214 @ 0x020bb214, 0x2c bytes, Thumb
 * func_020bb1d4 @ 0x020bb1d4, 0x40 bytes, Thumb
 * func_020bb1b0 @ 0x020bb1b0, 0x22 bytes, Thumb
 * func_020bb18c @ 0x020bb18c, 0x24 bytes, Thumb
 * func_020bb090 @ 0x020bb090, 0xfc bytes, Thumb
 * func_020bae60 @ 0x020bae60, 0x230 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    char pad_04[0x1510];
    int unk_1514;
    int unk_1518;
    int unk_151C;
    int unk_1520;
    char pad_1524[0x10];
    int unk_1534;
    char pad_1538[0x2c];
    int unk_1564;
    int unk_1568;
    int unk_156C;
    char pad_1570[0x8];
    int unk_1578;
    int unk_157C;
    char pad_1580[0x4];
    int unk_1584;
    char pad_1588[0x4];
    int unk_158C;
} UnkStruct_020bb99c;

struct Pair {
    int x;
    int y;
};

struct Big {
    u32 unk_00;
    unsigned char pad0[0x1208];
    u32 unk_120C;
    unsigned char pad_1210[0x310];
    u32 unk_1520;
    unsigned char pad_1524[0x8];
    s32 unk_152C;
    u32 unk_1530;
    unsigned char pad_1534[0x8];
    u16 unk_153C;
    u16 unk_153E;
    unsigned char pad_1540[0x30];
    u32 unk_1570;
    u32 unk_1574;
    u32 unk_1578;
    unsigned char pad_157C[0x10];
    u32 unk_158C;
};

typedef struct {
    char pad_00[0x1524];
    int unk_1524;
    char pad_1528[0x4];
    int unk_152C;
    int unk_1530;
    char pad_1534[0x40];
    int unk_1574;
} UnkStruct_020bb7a0;

typedef struct {
    char pad_00[0x1520];
    int unk_1520;
    int unk_1524;
    char pad_1528[0x158c - 0x1528];
    int unk_158C;
} UnkStruct_020bb75c;

typedef struct {
    char pad_00[0x1570];
    int unk_1570;
} UnkStruct_020bb608;

typedef struct S_020bb568 {
    char pad_00[0x120c];
    int unk_120C;
    char pad_1210[0x1524 - 0x1210];
    int unk_1524;
    int unk_1528;
    int unk_152C;
    int unk_1530;
    char pad_1534[0x1578 - 0x1534];
    int unk_1578;
    char pad_157C[0x1584 - 0x157c];
    int unk_1584;
    int unk_1588;
    int unk_158C;
} S_020bb568;

typedef struct UnkStruct_020bb4e0 {
    unsigned char pad_00[0x1208];
    int unk_1208;
    int unk_120C;
    unsigned char pad_1210[0x1528 - 0x1210];
    int unk_1528;
    unsigned char pad_152C[0x1570 - 0x152c];
    int unk_1570;
    int unk_1574;
    int unk_1578;
    unsigned char pad_157C[0x1584 - 0x157c];
    unsigned char *unk_1584;
    unsigned char pad_1588[0x158c - 0x1588];
    int unk_158C;
} UnkStruct_020bb4e0;

struct UnkStruct_020bb480 {
    char pad_00[0x120c];
    int unk_120C;
    char pad_1210[0x314];
    int unk_1524;
    char pad_1528[0x50];
    int unk_1578;
    int unk_157C;
    int unk_1580;
    char pad_1584[0x8];
    int unk_158C;
};

typedef struct {
    char pad_00[0x1208];
    int unk_1208;
    char pad_120C[0x1520 - 0x120c];
    int unk_1520;
    int unk_1524;
    char pad_1528[0x152c - 0x1528];
    int unk_152C;
    int unk_1530;
    char pad_1534[0x1578 - 0x1534];
    int unk_1578;
    char *unk_157C;
    char pad_1580[0x158c - 0x1580];
    int unk_158C;
} UnkStruct_020bb3f4;

typedef struct {
    char pad_00[0x1520];
    u32 flag;
    char pad_1524[0x158c - 0x1520 - 4];
    u32 mode;
} UnkStruct_020bb3a4;

typedef struct {
    char pad_00[0x120c];
    int unk_120C;
    char pad_1210[0x1524 - 0x1210];
    int unk_1524;
    char pad_1528[0x152c - 0x1528];
    int unk_152C;
    char pad_1530[0x158c - 0x1530];
    int unk_158C;
    int unk_1590;
} UnkStruct_020bb35c;

struct UnkStruct_020bb30c {
    char pad_00[0x120c];
    int unk_120C;
    char pad_1210[0x318];
    int unk_1528;
    char pad_152C[0x60];
    int unk_158C;
    int unk_1590;
};

struct UnkStruct_020bb290 {
    unsigned char pad_00[0x1520];
    int unk_1520;                 // offset 0x1520
    int unk_1524;                 // offset 0x1524
    unsigned char pad_1528[4];    // offset 0x1528
    int unk_152C;                 // offset 0x152c
    int unk_1530;                 // offset 0x1530
    unsigned char pad_1534[0x58]; // offset 0x1534..0x158b
    int unk_158C;                 // offset 0x158c
    int unk_1590;                 // offset 0x1590
};

typedef struct {
    char pad_00[0x1520];
    u32 flag;
    char pad_1524[0x158c - 0x1520 - 4];
    u32 mode;
} UnkStruct_020bb240;

typedef struct {
    int pad_00;
    u16 unk_04;
    u16 unk_06;
    int unk_08;
    int unk_0C;
} UnkStruct_020bb090;

struct Head {
    int unk_00;
    int unk_04;
};

struct UnkStruct_020bae60_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};

struct UnkStruct_020bae60 {
    int x;
    int y;
    short z;
};

extern void func_020bbc90(UnkStruct_020bb99c *p);
extern int func_020644cc(int a);
extern void func_0209e100(struct Pair *p, int n);
extern int func_020bbd30(void);
extern int func_020bbcfc(void *);
extern int func_020bbb20(void *);
extern void func_020bba14(void);
extern int *data_021f6cd8;
extern unsigned char data_021f8b14[];
extern void func_0209e474(void *p);
extern int func_0209dbe4(void *p);
extern int func_020c1608(unsigned char *dst, unsigned char *src);
extern signed char data_021f3b28[];
extern unsigned char data_021dc7a8[];
extern signed char data_020d28ac[][24];
extern int data_020e6070[];
extern int data_021fbe94;
extern int func_02002c4c(int, int, int, int, int, int);
extern int *data_020e5e0c[];
extern int func_02064b2c(int, void *, int, void *);
extern int func_02064af4(int, int, int);
extern int func_02002b40(unsigned char *p, int a, int b, int c);
extern int func_0209e380(unsigned long long *p, int a);
extern int data_021f6f70;
extern UnkStruct_020bb090 data_021f7270;
extern u16 data_021f6f74[];
extern struct Head data_021f75b0;
extern u16 data_021f87c0[];
extern char data_021f75b8[];
extern int data_021f8b44;
extern int data_021f87b8;
extern u8 data_021f6cbc;
extern int data_021f6ce8[];
extern int data_021f6ce0[];
extern u16 data_020e597c[];
extern void *func_020961a8(int a);
extern int func_020655c4(int a);

void func_020bb7e0(char *out, int a, int b);
int func_020bb6b0(int a, int b);
signed char func_020bb6a0(int unused, int row, int col);
int func_020bb214(int unused0, int uninit);
int func_020bb1d4(int unused, unsigned char *p);

UnkStruct_020bb99c *func_020bb99c(UnkStruct_020bb99c *p)
{
    p->unk_00 = 0;
    p->unk_1520 = 0;
    p->unk_157C = 0;
    p->unk_1584 = 0;
    p->unk_158C = 0;
    p->unk_1578 = -1;
    p->unk_1514 = 0;
    p->unk_1518 = 0;
    p->unk_151C = 0;
    p->unk_1564 = 0;
    p->unk_1568 = 0;
    p->unk_156C = 0;
    p->unk_1534 = 0;
    func_020bbc90(p);
    return p;
}

void func_020bb998(void *object) {}

void func_020bb8e0(struct Big *self)
{
    int ret;
    struct Pair stack;

    ret = func_020bb6b0((int) self, 0);
    switch (ret) {
        case 3:
        case 4:
            (*(struct Global8 { unsigned char pad0[5]; unsigned char flag; } *) data_021f3b28).flag = 1;
            break;
        default:
            break;
    }
    func_020bb7e0((char *) self, ret, ret);
    self->unk_00 = 1;
    self->unk_158C = 0;
    self->unk_152C = -1;
    self->unk_1530 = 2;
    self->unk_1574 = func_020644cc(2);
    self->unk_1570 = self->unk_1574;
    self->unk_1520 = 0;
    self->unk_1578 = 0;
    self->unk_120C = 0;
    stack.x = 0;
    stack.y = 0;
    func_0209e474((void *) (&stack));
    self->unk_153E = (u16) func_020bb1d4((int) self, (unsigned char *) (&stack));
    func_0209e100(&stack, 6);
    self->unk_153C = (u16) func_020bb214((int) self, (int) (&stack));
}

int func_020bb89c(void *param)
{
    int ret = 0;
    if (func_020bbd30() != 0 && func_020bbcfc((void *) data_021f8b14) != 0) {
        if (data_021f6cd8 != 0) {
            ret = func_020bbb20(param);
        } else {
            func_020bba14();
            ret = 1;
        }
    }
    return ret;
}

int func_020bb830(int a, int b)
{
    u64 t;
    int r;

    r = 0;
    t = 0;
    func_0209e474(&t);
    if (b != 3) {
        if (b != 4) {
            goto done;
        }
    }
    switch (func_0209dbe4(&t)) {
        case 0:
        case 1:
        case 2:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
            r = 2;
            break;
        default:
            r = 1;
            break;
    }
done:
    return r;
}

void func_020bb7e0(char *out, int a, int b)
{
    void *x;
    void *y;

    x = (void *) func_020bb830((int) out, a);
    y = (void *) func_020bb830((int) out, b);
    if (x) {
        *(void **) (out + 0x1534) = x;
    } else if (y) {
        *(void **) (out + 0x1534) = y;
    } else {
        *(void **) (out + 0x1534) = 0;
    }
    *(int *) (out + 0x1524) = a;
    *(int *) (out + 0x1528) = b;
}

void func_020bb7a0(UnkStruct_020bb7a0 *self, int param1)
{
    int flag;
    self->unk_152C = param1;
    if (param1 > self->unk_1524) {
        flag = 0;
        self->unk_1530 = flag;
    } else {
        flag = 1;
        self->unk_1530 = flag;
    }
    self->unk_1574 = func_020644cc(2);
}

int func_020bb75c(UnkStruct_020bb75c *self, int value)
{
    int flag = 0;

    if (value == -1) {
        goto end;
    }
    if (value == self->unk_1524) {
        flag = 1;
        goto end;
    }
    if (self->unk_1520 != 0) {
        goto end;
    }

    func_020bb7a0((UnkStruct_020bb7a0 *) self, value);
    flag = 1;
    self->unk_158C = flag;
    self->unk_1520 = flag;

end:
    return flag;
}

void func_020bb6d8(int self)
{
    unsigned char *base = data_021dc7a8;
    unsigned char buf[12];
    int status, t;

    ((unsigned int *) buf)[0] = 0;
    ((unsigned int *) buf)[1] = 0;
    func_0209e474((void *) buf);

    if (((data_021f3b28[4] + 6) % 24) == buf[2]) {
        return;
    }

    func_020c1608(&base[0x1737e], buf);

    status = func_020bb6b0(self, 1);
    switch (status) {
        case 3:
        case 4:
            base[0x17385] = 1;
            break;
    }

    if (func_020bb75c((UnkStruct_020bb75c *) self, status) == 0) {
        return;
    }

    t = (int) buf[2] - 6;
    if (t < 0) {
        t += 24;
    }
    base[0x17384] = (unsigned char) t;
}

int func_020bb6b0(int a, int b)
{
    int rem = (b + data_021f3b28[4]) % 24;
    return (int) func_020bb6a0(a, (unsigned char) data_021f3b28[2], rem);
}

signed char func_020bb6a0(int unused, int row, int col)
{
    return data_020d28ac[row][col];
}

int func_020bb66c(int a, int index, int c)
{
    int result = 0;
    if (func_02002c4c(data_020e6070[index], data_021fbe94, c, 16, 16, 47) != 0) {
        result = 1;
    }
    return result;
}

int func_020bb608(UnkStruct_020bb608 *param0, int *param1, int *param2, int param3, int param4)
{
    int result = 0;
    int idx;
    int val;
    if (param3 == 0) {
        int t = param4 * 2;
        idx = t + param0->unk_1570;
    } else {
        idx = param4;
    }
    val = data_020e5e0c[param3][idx];
    if (*param1 == 0) {
        *param1 = func_02064b2c(val, (*(void * *) &data_021fbe94), -4, param2);
        if (*param1 != 0) {
            result = 1;
        }
    } else {
        if (func_02064af4(val, *param1, *param2) != 0) {
            result = 1;
        }
    }
    return result;
}

void func_020bb568(S_020bb568 *p)
{
    int mode;
    int idx;

    if (p->unk_1530 == 0) {
        mode = 1;
        idx = p->unk_1524 + 1;
    } else {
        mode = 2;
        idx = p->unk_1524 - 1;
    }

    if (func_020bb66c((int) p, idx, 6) != 0) {
        if (func_020bb608((UnkStruct_020bb608 *) p, &p->unk_1584, &p->unk_1588, mode, idx) != 0) {
            func_020bb7e0((char *) p, p->unk_1524, idx);
            if (p->unk_1524 < 3 && p->unk_1528 >= 3) {
                func_020bbc90((UnkStruct_020bb99c *) p);
            }
            p->unk_1578 = 0;
            p->unk_120C = 0;
            p->unk_158C = 2;
        }
    }
}

void func_020bb4e0(UnkStruct_020bb4e0 *self)
{
    int idx;
    int t;
    int n;
    int off;

    idx = self->unk_1578;
    t = ((self->unk_1208 >> 8) - 8) & 0xff;
    if ((t >> 3) == idx) {
        off = (t >> 3) * 0x20;
        if (func_02002b40(self->unk_1584 + off, 6, 0x20, off) != 0) {
            n = self->unk_120C;
            idx = idx + 1;
            n = n + 1;
            if (idx >= 0x20) {
                idx = -1;
                n = 0x20;
                func_020bb7e0((char *) self, self->unk_1528, self->unk_1528);
                self->unk_1570 = self->unk_1574;
                self->unk_158C = 3;
            }
            self->unk_1578 = idx;
            self->unk_120C = n;
        }
    }
}

void func_020bb480(struct UnkStruct_020bb480 *self)
{
    int val = self->unk_1524;
    if (func_020bb66c((int) self, val, 6)) {
        if (func_020bb608((UnkStruct_020bb608 *) self, &self->unk_157C, &self->unk_1580, 0, val)) {
            self->unk_1578 = 0;
            self->unk_120C = 0x20;
            self->unk_158C = 4;
        }
    }
}

void func_020bb3f4(UnkStruct_020bb3f4 *self)
{
    int idx = self->unk_1578;
    int comp = (((self->unk_1208 >> 8) - 8) & 0xff) >> 3;
    if (comp != idx) {
        return;
    }
    if (func_02002b40((unsigned char *) (self->unk_157C + comp * 32), 6, 0x20, comp * 32) == 0) {
        return;
    }
    idx++;
    if (idx >= 0x20) {
        idx = -1;
        if (self->unk_152C == self->unk_1524) {
            self->unk_158C = 0;
            self->unk_152C = -1;
            self->unk_1530 = 2;
            self->unk_1520 = 0;
        } else {
            self->unk_158C = 1;
        }
    }
    self->unk_1578 = idx;
}

void func_020bb3a4(UnkStruct_020bb3a4 *self)
{
    if (self->flag == 0) {
        return;
    }
    switch (self->mode) {
        case 1:
            func_020bb568((S_020bb568 *) self);
            break;
        case 2:
            func_020bb4e0((UnkStruct_020bb4e0 *) self);
            break;
        case 3:
            func_020bb480((struct UnkStruct_020bb480 *) self);
            break;
        case 4:
            func_020bb3f4((UnkStruct_020bb3f4 *) self);
            break;
        case 0:
            break;
    }
}

void func_020bb35c(UnkStruct_020bb35c *self)
{
    int a = self->unk_1524;
    int b = self->unk_152C;
    int c;
    if (b > a) {
        c = a + 1;
    } else {
        c = a - 1;
    }
    func_020bb7e0((char *) self, a, c);
    self->unk_120C = 0;
    self->unk_158C = 2;
    self->unk_1590 = 0;
}

void func_020bb30c(struct UnkStruct_020bb30c *p)
{
    p->unk_1590++;
    if (p->unk_1590 >= 0x2a8) {
        func_020bb7e0((char *) p, p->unk_1528, p->unk_1528);
        p->unk_158C = 3;
    }
    p->unk_120C = (p->unk_1590 << 5) / 0x2a8;
}

void func_020bb2ec(unsigned char *r0)
{
    *(unsigned int *) (r0 + 0x120c) = 0x20;
    *(unsigned int *) (r0 + 0x158c) = 4;
    *(unsigned int *) (r0 + 0x1590) = 0;
}

void func_020bb290(struct UnkStruct_020bb290 *self)
{
    self->unk_1590++;
    if (self->unk_1590 < 0x2a8) {
        return;
    }
    if (self->unk_152C == self->unk_1524) {
        self->unk_158C = 0;
        self->unk_152C = -1;
        self->unk_1530 = 2;
        self->unk_1520 = 0;
        return;
    } else {
        self->unk_158C = 1;
        return;
    }
}

void func_020bb240(UnkStruct_020bb240 *self)
{
    if (self->flag == 0) {
        return;
    }
    switch (self->mode) {
        case 1:
            func_020bb35c((UnkStruct_020bb35c *) self);
            break;
        case 2:
            func_020bb30c((struct UnkStruct_020bb30c *) self);
            break;
        case 3:
            func_020bb2ec((unsigned char *) self);
            break;
        case 4:
            func_020bb290((struct UnkStruct_020bb290 *) self);
            break;
        case 0:
            break;
    }
}

int func_020bb214(int unused0, int uninit)
{
    unsigned long long local = 0;

    local = 0x0000000101000000ULL;
    return (unsigned short) ((func_0209e380(&local, uninit) % 64) * 8);
}

int func_020bb1d4(int unused, unsigned char *p)
{
    int rem;
    int t;
    int q;

    rem = (p[2] + 6) % 24;
    if (rem >= 12) {
        return 0x100;
    }

    t = rem * 60;
    q = ((t + p[1]) * 0x68000) / 0x2d0;

    return (unsigned) q << 4 >> 16;
}

int func_020bb1b0(void *arg)
{
    unsigned int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    return func_020bb1d4((int) arg, (unsigned char *) local);
}

// placeholder, not actually used
// placeholder, not actually used
void func_020bb18c(unsigned char *param0, int param1, unsigned short param2, unsigned int param3)
{
    unsigned char *ptr;
    unsigned int *ptr2;
    int offset;

    offset = param1 * 2;
    ptr = param0 + offset;
    *(unsigned short *) (ptr + 0x304) = param2;

    offset = param1 * 4;
    ptr2 = (unsigned int *) (param0 + offset);
    *(unsigned int *) ((unsigned char *) ptr2 + 0x308) = param3;
}

void func_020bb090(void)
{
    int parity;
    int y1;
    int span;
    int gB, gA, rB, rA, bB, bA;
    int mr, mg, c;
    int y, y0;
    int t, inv;
    int cA, cB;
    u16 *dst;
    volatile u16 w[6];

    parity = (data_021f6f70 + 1) % 2;
    w[3] = data_021f7270.unk_04;
    w[1] = w[3];
    w[4] = data_021f7270.unk_06;
    w[2] = w[4];
    dst = (u16 *) ((char *) data_021f6f74 + parity * 0x180);
    y0 = data_021f7270.unk_08;
    y1 = data_021f7270.unk_0C;
    y = 0;
    span = y1 - y0;
    cB = w[2];
    gB = ((u32) cB << 22) >> 27;
    cA = w[1];
    gA = ((u32) cA << 22) >> 27;
    rB = ((u32) (cB << 27)) >> 27;
    rA = ((u32) (cA << 27)) >> 27;
    bB = ((u32) cB << 17) >> 27;
    bA = ((u32) cA << 17) >> 27;
    for (; y < 0xc0; y++) {
        if (y <= y0) {
            w[0] = w[3];
        } else if (y >= y1) {
            w[0] = w[4];
        } else {
            t = ((y - y0) << 8) / span;
            inv = 0x100 - t;
            c = (int) (u16) ((bA * inv + bB * t) >> 8) << 10;
            mr = (u16) ((rA * inv + rB * t) >> 8);
            mg = (int) (u16) ((gA * inv + gB * t) >> 8) << 5;
            c = c | (mr | mg);
            w[0] = (u16) c;
        }
        *dst = w[0];
        dst++;
    }
    data_021f6f70 = parity;
}

void func_020bae60(void)
{
    int a;
    int e;
    int slot;
    u16 *pal;
    void *o;
    struct UnkStruct_020bae60_2 *sub;
    int v;
    int angle;
    int j, i, n;
    struct UnkStruct_020bae60 *p;
    struct UnkStruct_020bae60 *end;
    int t1, t2;
    int da, dang;
    int x;
    u16 c;
    unsigned int t;
    int lo, hi;
    int *ap;
    int prod;
    int d;
    int w2;

    a = 0;
    e = 0;
    slot = (data_021f75b0.unk_04 + 1) % 2;
    pal = (u16 *) ((char *) data_021f87c0 + slot * 0x180);
    o = func_020961a8(4);
    if (o != 0) {
        sub = (struct UnkStruct_020bae60_2 *) ((char *) o + 0x5c);
        if (sub != 0) {
            int *gp;
            int w;
            a = sub->unk_00 >> 3;
            gp = &data_021f8b44;
            w = sub->unk_08;
            v = (w - *gp) >> 4;
            if (v < 0) {
                e = (v * -0xb0) >> 8;
            } else {
                e = (-(v * 0x80)) >> 8;
            }
            *gp = w;
        }
    }
    ap = &data_021f87b8;
    angle = *ap + 0x60 + e;
    if (angle >= 0x10000) {
        angle -= 0x10000;
    }
    *ap = angle;

    if (data_021f6cbc == 0) {
        data_021f6cbc = 1;
        for (i = 0; i < 2; i++) {
            data_021f6ce8[i] = a;
            data_021f6ce0[i] = angle;
            p = (struct UnkStruct_020bae60 *) (data_021f75b8 + i * 0x900);
            for (j = 0; j < 0xc0; j++) {
                t1 = (-(j << 8)) / 0xc0;
                p->z = (short) (0x10000 / (t1 + 0x200));
                w2 = (p->z - 0x100) << 7;
                w2 = -w2;
                p->x = a + w2;
                t2 = ((0xc000 * j) / 0xc0 + 0x3000) / 0xc0;
                p->y = angle + 0xc0 * ((t2 * t2) >> 8);
                p++;
            }
        }
    }

    da = a - data_021f6ce8[slot];
    dang = angle - data_021f6ce0[slot];
    if (da != 0 || dang != 0) {
        data_021f6ce8[slot] = a;
        data_021f6ce0[slot] = angle;
        p = (struct UnkStruct_020bae60 *) (data_021f75b8 + slot * 0x900);
        end = (struct UnkStruct_020bae60 *) ((char *) p + 0x900);
        if (dang == 0) {
            for (; p < end; p++) {
                p->x += da;
            }
        } else if (da == 0) {
            for (; p < end; p++) {
                p->y += dang;
            }
        } else {
            for (; p < end; p++) {
                p->x += da;
                p->y += dang;
            }
        }
    }

    n = 0;
    x = func_020655c4(1);
    if (x == data_020e597c[slot]) {
        goto done;
    }
    data_020e597c[slot] = (u16) x;
    c = (u16) (x | 0x1000);
    for (; n < 0x77; n++) {
        *pal = c;
        pal++;
    }
    for (; n < 0x97; n++) {
        prod = x;
        prod = (n - 0x77) * prod;
        d = (int) ((unsigned int) prod >> 5);
        *pal = (u16) ((x - d) | 0x1000);
        pal++;
    }
    for (; n < 0x98; n++) {
        *pal = 0x10;
        pal++;
    }
    for (; n < 0xa8; n++) {
        t = (unsigned int) ((n - 0x98) * 0x10) / 0x10;
        lo = 0x10 - (int) t;
        hi = 0x10 - lo;
        *pal = (u16) (lo | (hi << 8));
        pal++;
    }
    for (; n < 0xc0; n++) {
        *pal = 0x1000;
        pal++;
    }
done:
    data_021f75b0.unk_04 = slot;
}
