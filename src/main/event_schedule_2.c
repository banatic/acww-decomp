/* event_schedule_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02040da8 @ 0x02040da8, 0x9a bytes, Thumb
 * func_02040c90 @ 0x02040c90, 0x118 bytes, Thumb
 * func_02040c80 @ 0x02040c80, 0x10 bytes, Thumb
 * func_02040bfc @ 0x02040bfc, 0x84 bytes, Thumb
 * func_02040bcc @ 0x02040bcc, 0x2e bytes, Thumb
 * func_02040ba0 @ 0x02040ba0, 0x2c bytes, Thumb
 * func_02040b6c @ 0x02040b6c, 0x34 bytes, Thumb
 * func_02040b20 @ 0x02040b20, 0x4c bytes, Thumb
 * func_02040adc @ 0x02040adc, 0x44 bytes, Thumb
 * func_02040a90 @ 0x02040a90, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

typedef union {
    u64 q;
    u8 b[8];
} UnkStruct_02040c90;

typedef struct {
    u8 d[0x14];
} UnkStruct_02040c90_2;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
} UnkStruct_02040c90_4;

typedef struct {
    u8 pad_00[0x34];
    u64 unk_34;
} UnkStruct_02040c90_3;

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
    unsigned char unk_03;
} Result_02040bfc;

typedef struct {
    unsigned char b[12];
} UnkStruct_02040b20;

typedef struct {
    unsigned char x, y, z;
} UnkStruct_02040b20_2;

typedef struct {
    unsigned char b[12];
} UnkStruct_02040a90;

typedef struct {
    unsigned char x, y, z;
} UnkStruct_02040a90_2;

extern void func_0209e474(void *);
extern int func_0209ded0(void);
extern void func_02040a10(void *obj);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern int func_0203fea0(void *dst, void *src);
extern unsigned char *func_020409c8(void *obj, int n);
extern int func_0203fd38(int a, void *b, void *c);
extern void func_020408a8(void *p);
extern u32 data_021c7584;
extern void func_0209e314(UnkStruct_02040c90 *, UnkStruct_02040c90 *);
extern void func_0204101c(UnkStruct_02040c90_3 *);
extern int func_02041140(UnkStruct_02040c90_3 *, UnkStruct_02040c90_2 *, UnkStruct_02040c90 *);
extern void func_02040e44(UnkStruct_02040c90_3 *, UnkStruct_02040c90_2 *, int *, UnkStruct_02040c90 *);
extern void func_02040f8c(UnkStruct_02040c90_3 *, UnkStruct_02040c90_2 *, int *, u8 *, UnkStruct_02040c90 *);
extern void func_02040f04(UnkStruct_02040c90_3 *, UnkStruct_02040c90_2 *, int *, UnkStruct_02040c90 *);
extern void func_020ae190(void);
extern unsigned char data_021f39c0[];
extern int func_0203fae4(void);
extern void *func_02040980(void *context);
extern int func_0203fcb4(int a, void *b, int c);
extern int data_021dc7a8;
extern void func_0209e140(int, int);
extern void func_0209e29c(int, int);
extern unsigned char data_021f39c8[];
extern int func_0209dcdc(UnkStruct_02040b20_2 *, unsigned char *);
extern unsigned char data_021f39cc[];

int func_02040bcc(int arg0, int arg1);

void func_02040da8(void *obj)
{
    int flag;
    Pair a;
    unsigned char b[8];
    unsigned char c[8];
    unsigned char buf[0x58];
    int n;
    unsigned char *p;
    int i;
    int last;
    int t;

    a.unk_00 = 0;
    a.w1 = 0;
    n = func_0209ded0();
    func_0209e474(&a);
    func_02040a10(obj);
    MI_CpuCopy8(&a, b, 8);
    func_0203fea0(buf, b);
    func_0209e474(&a);
    last = n - 1;
    flag = 0;
    for (i = 0; i <= last; i++) {
        p = func_020409c8(obj, i + 1);
        if (p == 0) {
            continue;
        }
        if (p[2] == 0x63) {
            continue;
        }
        MI_CpuCopy8(&a, c, 8);
        if (func_0203fd38(p[2], c, buf) == 0) {
            t = 1;
        } else {
            t = flag;
        }
        if (t != 0) {
            func_020408a8(p);
        } else if (i != last && p[2] == 0x45) {
            func_020408a8(p);
        }
    }
}

void func_02040c90(UnkStruct_02040c90_3 *a0, int a1)
{
    UnkStruct_02040c90 s1;
    UnkStruct_02040c90 s2;
    u8 buf[8];
    int v;
    UnkStruct_02040c90 c1;
    UnkStruct_02040c90 c2;
    UnkStruct_02040c90 c3;
    UnkStruct_02040c90 c4;
    UnkStruct_02040c90_2 big;
    u32 t0;
    u32 v1;
    UnkStruct_02040c90_4 *p;
    UnkStruct_02040c90_4 *e;
    int j;

    s1.q = 0;
    s2.q = 0;
    func_0209e474((void *) (&s1));
    t0 = (u32) func_0209ded0();
    data_021c7584 = s1.b[2];
    func_0209e314(&s1, &s2);
    if (a0->unk_34 == 0 || a0->unk_34 != s2.q || a1) {
        p = (UnkStruct_02040c90_4 *) func_020409c8((void *) a0, 1);
        for (j = 0; j < 5; j++) {
            buf[j] = p->unk_02;
            p++;
        }
        buf[5] = 0x63;
        func_0204101c(a0);
        MI_CpuCopy8(&s2, &c1, 8);
        v = func_02041140(a0, &big, &c1);
        MI_CpuCopy8(&s2, &c2, 8);
        func_02040e44(a0, &big, &v, &c2);
        MI_CpuCopy8(&s2, &c3, 8);
        func_02040f8c(a0, &big, &v, buf, &c3);
        MI_CpuCopy8(&s2, &c4, 8);
        func_02040f04(a0, &big, &v, &c4);
        MI_CpuCopy8(&s2, &a0->unk_34, 8);
    }
    func_02040da8((void *) a0);
    v1 = (u32) func_02040bcc((int) a0, 0x3d);
    if (v1 - t0 <= 1) {
        e = (UnkStruct_02040c90_4 *) func_020409c8((void *) a0, v1);
        if (e != 0 && e->unk_04 == 0) {
            func_020ae190();
            e->unk_04 = 1;
        }
    }
}

void func_02040c80(void)
{
    func_02040c90((UnkStruct_02040c90_3 *) ((void *) data_021f39c0), 0);
}

void func_02040bfc(void)
{
    int buf8[2];
    unsigned char buf8b[8];
    unsigned char v;
    unsigned char f2;
    unsigned char f3;
    Result_02040bfc *result;
    int rv;
    unsigned char *base;

    if (func_0203fae4() == 1) {
        return;
    }

    base = (unsigned char *) &data_021dc7a8;

    buf8[0] = 0;
    buf8[1] = 0;
    func_0209e474(buf8);
    v = ((unsigned char *) buf8)[2];
    if ((*(int *) &data_021c7584) == v) {
        return;
    }
    (*(int *) &data_021c7584) = v;

    result = func_02040980(base + 0x17218);
    if (result == 0) {
        return;
    }
    f2 = result->unk_02;
    if (f2 == 0x63) {
        return;
    }

    MI_CpuCopy8((const void *) buf8, buf8b, 8);
    rv = func_0203fcb4(f2, buf8b, 0);

    f3 = result->unk_03;
    switch (f3) {
        case 0:
            if (rv == 2) {
                result->unk_03 = 1;
            }
            break;
        case 1:
            if (rv == 0) {
                func_020408a8((void *) result);
            }
            break;
        default:
            break;
    }
}

int func_02040bcc(int arg0, int arg1)
{
    int result = 0;
    unsigned char *p = (unsigned char *) func_020409c8((void *) arg0, 1);
    int i = result;
    for (; i < 5; i++) {
        if (arg1 == p[2]) {
            result = i + 1;
            break;
        }
        p += 6;
    }
    return result;
}

void func_02040ba0(unsigned int param)
{
    if (param >= 62 && param < 70) {
        unsigned char *p = func_02040980(data_021f39c0);
        if (p != 0) {
            if (param == p[2]) {
                p[4] = 1;
            }
        }
    }
}

void func_02040b6c(int a0, int a1)
{
    func_0209e474((void *) ((unsigned char *) a0));
    if (a1 == 1) {
        int s = func_0209ded0() + 1;
        func_0209e140(a0, s);
    } else {
        int s = 7 - func_0209ded0();
        func_0209e29c(a0, s);
    }
}

int func_02040b20(UnkStruct_02040b20 p)
{
    UnkStruct_02040b20_2 t;
    int ret = 0;
    int r;
    unsigned char *g = data_021f39c8;
    unsigned char g2;

    g2 = g[2];
    if (!(g2 == 0 && g[1] == 1 && g[0] == 1)) {
        t.z = g2;
        t.y = p.b[3];
        t.x = p.b[2];
        r = func_0209dcdc(&t, g);
        if (r >= 0 && r < 7) {
            ret = 1;
        }
    }
    return ret;
}

void func_02040adc(void *p0, int flag)
{
    int local[2];
    unsigned char *base = data_021f39c8;
    if (flag == 0) {
        base[0] = 1;
        base[1] = 1;
        base[2] = 0;
        base[3] = 0;
        return;
    }
    local[0] = 0;
    local[1] = 0;
    func_02040b6c((int) local, (int) p0);
    base[0] = ((unsigned char *) local)[3];
    base[1] = ((unsigned char *) local)[4];
    base[2] = ((unsigned char *) local)[5];
}

int func_02040a90(UnkStruct_02040a90 p)
{
    UnkStruct_02040a90_2 t;
    int ret = 0;
    int r;
    unsigned char *g = data_021f39cc;
    unsigned char g2;

    g2 = g[2];
    if (!(g2 == 0 && g[1] == 1 && g[0] == 1)) {
        t.z = g2;
        t.y = p.b[3];
        t.x = p.b[2];
        r = func_0209dcdc((UnkStruct_02040b20_2 *) (&t), g);
        if (r >= 0 && r < 7) {
            ret = 1;
        }
    }
    return ret;
}
