/* turnip_prices: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02087850 @ 0x02087850, 0x2 bytes, Thumb
 * func_0208784c @ 0x0208784c, 0x2 bytes, Thumb
 * func_02087830 @ 0x02087830, 0x1c bytes, Thumb
 * func_02087800 @ 0x02087800, 0x30 bytes, Thumb
 * func_020877dc @ 0x020877dc, 0x22 bytes, Thumb
 * func_020877ac @ 0x020877ac, 0x30 bytes, Thumb
 * func_02087798 @ 0x02087798, 0x14 bytes, Thumb
 * func_02087784 @ 0x02087784, 0x14 bytes, Thumb
 * func_02087770 @ 0x02087770, 0x14 bytes, Thumb
 * func_020876f0 @ 0x020876f0, 0x80 bytes, Thumb
 * func_020876c8 @ 0x020876c8, 0x28 bytes, Thumb
 * func_02087500 @ 0x02087500, 0x1c6 bytes, Thumb
 * func_020874c4 @ 0x020874c4, 0x3c bytes, Thumb
 * func_02087480 @ 0x02087480, 0x42 bytes, Thumb
 * func_020873b4 @ 0x020873b4, 0xca bytes, Thumb
 * func_02087358 @ 0x02087358, 0x5c bytes, Thumb
 * func_020872d0 @ 0x020872d0, 0x88 bytes, Thumb
 * func_02087274 @ 0x02087274, 0x5c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020876f0 {
    char pad_00[10];
    char arr[32];
};

typedef struct {
    char pad_00[8];
    short unk_08;
    unsigned char unk_0A;
} UnkStruct_020876c8;

struct UnkStruct_02087500 {
    u8 pad_00[8]; // 0x00
    u16 unk_08;   // 0x08
    u8 data[14];  // 0x0a
    u8 unk_18;    // 0x18
};

typedef struct {
    int x;
    int y;
} Pair;

typedef struct {
    unsigned char unk_00, unk_01, unk_02, unk_03, unk_04, unk_05, unk_06, unk_07;
} UnkStruct_02087358;

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair_020872d0;

typedef struct {
    unsigned char unk_00, unk_01, unk_02, unk_03, unk_04, unk_05, unk_06, unk_07;
} UnkStruct_02087274;

extern int func_020644b4(int);
extern int func_020644cc(int);
extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern void func_0209e474(void *p);
extern int func_0209ded0(void);
extern int func_0206f798(void);
extern int func_0206f7a4(void);
extern void func_0209dfd8(void *dst, const void *src, int size, int d, int e);
extern void func_0209e140(void *p, int v);
extern int func_0209de88(int year, int month, int day);
extern int func_0209e3ac(void *p, void *q, int v);
extern int func_0209e380(void *p, void *q);
extern void MI_CpuCopy8(const void *src, void *dst, int size);
extern unsigned char data_021dc7a8[];
extern void func_0209f100(void *p, int n);

void func_02087500(struct UnkStruct_02087500 *s, int flag);
void func_02087358(void *self, void *src);
void func_020872d0(void *obj);
void func_02087274(void *self, void *src);

void func_02087850(void *self) {}

void func_0208784c(void *self) {}

void func_02087830(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    p[0x18] = 0xff;
    *(unsigned short *) (p + 8) = 0;
    p[0] = 1;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    p[4] = 1;
    p[5] = 1;
    p[6] = 0;
    p[7] = 0;
}

void func_02087800(int param1)
{
    int local[2];

    func_02087500((struct UnkStruct_02087500 *) param1, 0);
    local[0] = 0;
    local[1] = 0;
    func_0209e474((void *) local);
    func_02087358((void *) param1, (void *) local);
    func_02087274((void *) param1, (void *) local);
}

int func_020877dc(int r0, int r1, int r2)
{
    int r5 = r0;
    int r4 = r1;
    int r0_2 = r2;
    int r0_3 = func_020644b4(r0_2);
    unsigned char r1_2 = *(unsigned char *) (r5 + 0xa);
    int r0_4 = r4 + r0_3;
    int r1_3 = r1_2 * r0_4;
    int r0_5 = r1_3 >> 12;
    unsigned char r0_6 = (unsigned char) (r0_5 & 0xff);
    return r0_6;
}

void func_020877ac(unsigned char *base, int start, int end)
{
    int key = 0xca4;
    int i;
    for (i = start; i < end; i++) {
        *(base + i + 0xa) = (unsigned char) func_020877dc((int) base, key, 0x29);
        key -= 0x66;
    }
}

int func_02087798(int x)
{
    return func_020877dc(x, 0x666, 0x68f);
}

int func_02087784(int a)
{
    return func_020877dc(a, 0x0ccd, 0x09c3);
}

int func_02087770(int a)
{
    return func_020877dc(a, 0x1666, 0x9c3);
}

void func_020876f0(struct UnkStruct_020876f0 *p)
{
    int v = func_020644cc(6) + 7;
    func_020877ac((unsigned char *) p, 2, v - 3);
    p->arr[v - 3] = (char) func_02087784((int) p);
    p->arr[v - 2] = (char) func_02087784((int) p);
    p->arr[v] = (char) func_020877dc((int) p, 0x1b33, 0x4f6);
    p->arr[v - 1] = (char) func_020877dc((int) p, 0x168f, 0x4a4);
    p->arr[v + 1] = (char) func_020877dc((int) p, 0x168f, 0x4a4);
    func_020877ac((unsigned char *) p, v + 2, 14);
}

int func_020876c8(UnkStruct_020876c8 *ptr)
{
    int y;
    int x;
    y = func_020644b4(0x419a);
    x = ptr->unk_0A;
    y += 0x2000;
    x = x * y;
    ptr->unk_08 = (short) (x >> 12);
    return 0;
}

void func_02087500(struct UnkStruct_02087500 *s, int flag)
{
    if (s->unk_18 != 0xff) {
        int r = func_020644cc(0x65);
        switch (s->unk_18) {
            case 0:
                if (r < 0x1e) {
                    s->unk_18 = 1;
                } else if (r < 0x41) {
                    s->unk_18 = 3;
                } else if (r < 0x50) {
                    s->unk_18 = 2;
                }
                break;
            case 1:
                if (r < 0x14) {
                    s->unk_18 = 3;
                } else if (r < 0x41) {
                    s->unk_18 = 0;
                } else if (r < 0x55) {
                    s->unk_18 = 2;
                }
                break;
            case 2:
                if (r < 0x2d) {
                    s->unk_18 = 1;
                } else if (r < 0x46) {
                    s->unk_18 = 3;
                } else if (r < 0x5f) {
                    s->unk_18 = 0;
                }
                break;
            case 3:
                if (r < 0x19) {
                    s->unk_18 = 1;
                } else if (r < 0x46) {
                    s->unk_18 = 0;
                } else if (r < 0x55) {
                    s->unk_18 = 2;
                }
                break;
        }
        if (flag) {
            s->unk_18 = 2;
        }
    } else {
        s->unk_18 = func_020644cc(4);
    }

    s->unk_08 = 0;
    MI_CpuFill8(s->data, 0, 14);
    s->data[0] = func_020644cc(0x15) + 0x5a;
    s->data[1] = s->data[0];

    switch (s->unk_18) {
        case 0:
            s->data[2] = (u8) func_02087784((int) s);
            s->data[3] = (u8) func_02087798((int) s);
            s->data[4] = (u8) func_02087798((int) s);
            s->data[5] = (u8) func_02087798((int) s);
            s->data[6] = (u8) func_02087784((int) s);
            s->data[7] = (u8) func_02087784((int) s);
            s->data[8] = (u8) func_02087784((int) s);
            s->data[9] = (u8) func_02087798((int) s);
            s->data[10] = (u8) func_02087798((int) s);
            s->data[11] = (u8) func_02087784((int) s);
            s->data[12] = (u8) func_02087784((int) s);
            s->data[13] = (u8) func_02087784((int) s);
            break;
        case 1: {
            int index = func_020644cc(4) + 8;
            s->data[index] = (u8) func_020876c8((UnkStruct_020876c8 *) s);
            func_020877ac((unsigned char *) s, 2, index - 2);
            s->data[index - 1] = (u8) func_02087770((int) s);
            s->data[index + 1] = (u8) func_02087770((int) s);
            s->data[index - 2] = (u8) func_02087784((int) s);
            s->data[index + 2] = (u8) func_02087784((int) s);
            func_020877ac((unsigned char *) s, index + 3, 0xe);
            break;
        }
        case 2:
            func_020877ac((unsigned char *) s, 2, 0xe);
            break;
        case 3:
            func_020876f0((struct UnkStruct_020876f0 *) s);
            break;
    }
}

int func_020874c4(unsigned char *arg)
{
    int flag = 0;
    int local[3];
    int status;
    int index;
    unsigned char c;
    unsigned short h;
    c = 0;
    local[c] = flag;
    local[1] = flag;
    func_0209e474(local);
    if (((unsigned char *) local)[2] >= 12) {
        flag++;
    }
    status = func_0209ded0();
    index = (status << 1) + flag;
    c = (arg + index)[10];
    if (c != 0) {
        return c;
    }
    h = *((unsigned short *) (arg + 8));
    if (h == 0) {
        return c;
    }
    return h;
}

void func_02087480(void *arg)
{
    Pair pos;
    if (func_0206f798() || func_0206f7a4()) {
        pos.x = 0;
        pos.y = 0;
        func_0209e474((void *) (&pos));
        func_02087500((struct UnkStruct_02087500 *) arg, 1);
        func_02087358(arg, (void *) (&pos));
        func_02087274(arg, (void *) (&pos));
    }
}

void func_020873b4(void *param, int days)
{
    u8 data[16];
    int r;
    int a;
    int b;

    func_0209dfd8(data, param, 6, 0, 0);

    *(u32 *) &data[8] = 0;
    *(u32 *) &data[12] = 0;
    func_0209e474(&data[8]);

    if (!(data[13] == 0 && data[12] == 1 && data[11] == 1)) {
        if (data[10] < 6) {
            func_0209e140(&data[8], 1);
            data[10] = 6;
            data[9] = 0;
            data[8] = 0;
        }
    }

    r = func_0209e3ac(&data[8], data, 0x38);
    func_020872d0(param);

    if (r == 1) {
        a = func_0209de88(data[5], data[4], data[3]);
        b = func_0209de88(data[13], data[12], data[11]);
        if (b < a || func_0209e380(data, &data[8]) >= 7) {
            func_02087500((struct UnkStruct_02087500 *) param, 0);
            func_02087358(param, &data[8]);
        }
    } else if (r == -1) {
        func_02087500((struct UnkStruct_02087500 *) param, 1);
        func_02087358(param, &data[8]);
        func_02087274(param, &data[8]);
    }
}

void func_02087358(void *self, void *src)
{
    UnkStruct_02087358 info;
    char *out = (char *) self;
    *(unsigned int *) &info = 0;
    *(unsigned int *) ((char *) &info + 4) = 0;
    if (src == 0) {
        func_0209e474((void *) (&info));
    } else {
        MI_CpuCopy8(src, &info, 8);
    }
    if (info.unk_05 == 0) {
        if (info.unk_04 == 1) {
            if (info.unk_03 == 1) {
                goto skip;
            }
        }
    }
    if (info.unk_02 < 6) {
        func_0209e140((void *) (&info), 1);
    }
skip:
    out[2] = info.unk_05;
    out[1] = info.unk_04;
    out[0] = info.unk_03;
}

void func_020872d0(void *obj)
{
    Pair_020872d0 a;
    Pair_020872d0 b;

    func_0209dfd8(&a, (char *) obj + 4, 6, 0, 0);
    b.unk_00 = 0;
    b.w1 = 0;
    func_0209e474(&b);
    if (((unsigned char *) &b)[5] != 0 || ((unsigned char *) &b)[4] != 1 || ((unsigned char *) &b)[3] != 1) {
        if (((unsigned char *) &b)[2] < 6) {
            func_0209e140(&b, 1);
            ((unsigned char *) &b)[2] = 6;
            ((unsigned char *) &b)[1] = 0;
            ((unsigned char *) &b)[0] = 0;
        }
    }
    if (func_0209e3ac(&b, &a, 0x38) == 1) {
        if (func_0209e380(&a, &b) >= 7) {
            func_0209f100(data_021dc7a8, 4);
            func_02087274(obj, &b);
        }
    }
}

void func_02087274(void *self, void *src)
{
    UnkStruct_02087274 info;
    char *out = (char *) self;
    *(unsigned int *) &info = 0;
    *(unsigned int *) ((char *) &info + 4) = 0;
    if (src == 0) {
        func_0209e474((void *) (&info));
    } else {
        MI_CpuCopy8(src, &info, 8);
    }
    if (info.unk_05 == 0) {
        if (info.unk_04 == 1) {
            if (info.unk_03 == 1) {
                goto skip;
            }
        }
    }
    if (info.unk_02 < 6) {
        func_0209e140((void *) (&info), 1);
    }
skip:
    out[6] = info.unk_05;
    out[5] = info.unk_04;
    out[4] = info.unk_03;
}
