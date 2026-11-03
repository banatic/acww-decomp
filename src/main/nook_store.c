/* nook_store: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aef5c @ 0x020aef5c, 0x18 bytes, Thumb
 * func_020aef44 @ 0x020aef44, 0x18 bytes, Thumb
 * func_020aef2c @ 0x020aef2c, 0x18 bytes, Thumb
 * func_020aef28 @ 0x020aef28, 0x4 bytes, Thumb
 * func_020aed60 @ 0x020aed60, 0x1c8 bytes, Thumb
 * func_020aed38 @ 0x020aed38, 0x28 bytes, Thumb
 * func_020aece8 @ 0x020aece8, 0x50 bytes, Thumb
 * func_020aecb8 @ 0x020aecb8, 0x30 bytes, Thumb
 * func_020aec90 @ 0x020aec90, 0x28 bytes, Thumb
 * func_020aec68 @ 0x020aec68, 0x28 bytes, Thumb
 * func_020aec40 @ 0x020aec40, 0x28 bytes, Thumb
 * func_020aebcc @ 0x020aebcc, 0x74 bytes, Thumb
 * func_020aeb9c @ 0x020aeb9c, 0x30 bytes, Thumb
 * func_020aeb6c @ 0x020aeb6c, 0x30 bytes, Thumb
 * func_020aea84 @ 0x020aea84, 0xe8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020aed38 {
    int unk_00;
    int unk_04;
};

typedef struct {
    unsigned int pad_00;
    unsigned short arr[43];
    union {
        unsigned short raw;
        struct {
            unsigned short f0 : 5;
            unsigned short counter : 4;
            unsigned short f1 : 7;
        } bits;
    } unk_5A;
} UnkStruct_020aebcc;

struct UnkStruct_020aea84 {
    u8 pad_00[3];
    u8 unk_03;
};

extern unsigned char data_020d1e1c[];
extern int func_020af028(unsigned short *);
extern unsigned char data_020d1e14[];
extern unsigned char data_020d1e30[];
extern u32 data_021f4a00;
extern u16 data_021f4abc[7];
extern u16 data_021f4a20;
extern u16 data_021f4a2c;
extern u16 data_021f4a38;
extern u16 data_021f4a50;
extern u16 data_021f4a5c;
extern u16 data_021f4a74;
extern u16 data_021f4a8c;
extern void func_020051b0(void *);
extern void __register_global_object(void *, void *, void *);
extern u32 func_020aefec(u8 *);
extern int func_0204bcdc(u16 *);
extern u32 func_0204bc64(void *);
extern int func_020644cc(int);
extern int func_020aefd4(unsigned short *);
extern void func_020b0164(void *buffer, int *index, int a, int b, unsigned int count, int unused, unsigned char flag);
extern unsigned int func_020aefbc(unsigned short *p);
extern unsigned short data_020d1e5c[];
extern int func_020aefa4(unsigned short *);
extern void func_020b00fc(void *buffer, int *index, int a, int b, unsigned int count, int unused, unsigned char flag);
extern int func_020aef8c(unsigned short *);
extern int func_020aef74(unsigned short *);
extern int data_021f395c;
extern int func_020ad798(void);
extern int func_020af9f0(void *);
extern void *func_020af898(void *);
extern void *func_0204e414(void);
extern void *func_0204f694(void *, int);
extern void *func_02037e0c(void *, int, int, int);
extern int func_0204bba8(void *);
extern u16 func_0204bb68(void *);
extern int func_02037e44(void *, u16 *, int, int, int);
extern void func_020af004(void *, void *);
extern int func_020afc84(u32 *);
extern void func_0209e474(u32 *);
extern void func_020afcd4(void);
extern struct UnkStruct_020aea84 *func_020afad4(void *);
extern void func_020af3a0(void *, int);

int func_020aef5c(unsigned short *argument0)
{
    int result;
    unsigned char value;

    result = func_020af028((unsigned short *) argument0);
    value = data_020d1e1c[result];
    return value;
}

int func_020aef44(unsigned short *argument0)
{
    int index;
    unsigned char result;

    index = func_020af028((unsigned short *) argument0);
    result = data_020d1e14[index];
    return result;
}

int func_020aef2c(unsigned short *argument0)
{
    int result;
    result = func_020af028((unsigned short *) argument0);
    return data_020d1e30[result];
}

int func_020aef28(void)
{
    return 1;
}

inline static int EqA(u16 *p, u16 *q)
{
    if (func_0204bc64(p) == func_0204bc64(q)) {
        return 1;
    }
    return 0;
}

inline static int EqB(u16 x, u16 y)
{
    if (x == y) {
        return 1;
    }
    return 0;
}

inline char *inline_fn(char *arg0, u32 arg1)
{
    return arg0 + ((arg1 + func_020644cc(2)) * 2);
}

void func_020aed60(u8 *a, u32 *b)
{
    int mode;
    int count;
    int result;
    u32 i;
    u32 start;
    u16 val;
    u16 *base;
    u16 *p;
    u16 *q;
    if ((data_021f4a00 & 1) == 0) {
        data_021f4abc[0] = 0x1369;
        __register_global_object((void *) (&data_021f4abc[0]), (((void *) func_020051b0)), (void *) (&data_021f4a20));
        data_021f4abc[1] = 0x1378;
        __register_global_object((void *) (&data_021f4abc[1]), (((void *) func_020051b0)), (void *) (&data_021f4a2c));
        data_021f4abc[2] = 0x1376;
        __register_global_object((void *) (&data_021f4abc[2]), (((void *) func_020051b0)), (void *) (&data_021f4a38));
        data_021f4abc[3] = 0x1374;
        __register_global_object((void *) (&data_021f4abc[3]), (((void *) func_020051b0)), (void *) (&data_021f4a50));
        data_021f4abc[4] = 0x156c;
        __register_global_object((void *) (&data_021f4abc[4]), (((void *) func_020051b0)), (void *) (&data_021f4a5c));
        data_021f4abc[5] = 0x136b;
        __register_global_object((void *) (&data_021f4abc[5]), (((void *) func_020051b0)), (void *) (&data_021f4a74));
        data_021f4abc[6] = 0x137a;
        __register_global_object((void *) (&data_021f4abc[6]), (((void *) func_020051b0)), (void *) (&data_021f4a8c));
        data_021f4a00 |= 1;
    }
    if (func_020af028((unsigned short *) a) == 0) {
        mode = -3;
    } else {
        mode = 0;
    }
    start = *b;
    func_020b00fc(a + 4, (int *) b, 0, mode + 7, func_020aefec(a), 0x25, 0);
    if (func_020af028((unsigned short *) a) != 0) {
        goto after_loop;
    }
    count = 0;
    i = 0;
    base = (u16 *) (a + (start * 2));
    while (i < func_020aefec(a)) {
        p = (u16 *) ((a + 4) + ((start + i) * 2));
        if (func_0204bcdc(p) != 0) {
            u16 tmp = 3;
            result = EqA(p, &tmp);
        } else {
            q = base + i;
            result = EqB(q[2], 3);
        }
        if (result != 0) {
            count++;
        }
        i++;
    }

    if (count == 0) {
        char *p_base = ((char *) a) + 4;
        *((u16 *) inline_fn(p_base, start)) = 3;
    }
after_loop:
    i = 0;

    base = (u16 *) (a + (start * 2));
    while (i < func_020aefec(a)) {
        p = (base + i) + 2;
        val = *p;
        *p = data_021f4abc[val];
        i++;
    }
}

void func_020aed38(struct UnkStruct_020aed38 *a, int *b)
{
    int v;
    v = func_020aefd4((unsigned short *) a);
    func_020b0164(&a->unk_04, b, 0, 0, v, 0x25, 0);
}

void func_020aece8(unsigned short *param0, unsigned int *param1)
{
    unsigned int start;
    unsigned int i;
    unsigned short *p;

    start = *param1;
    func_020b00fc((void *) (param0 + 2), (int *) param1, 0, 12, func_020aefbc(param0), 37, 0);

    for (i = start; i < start + func_020aefbc(param0); i++) {
        p = param0 + i;
        p[2] = data_020d1e5c[p[2]];
    }
}

void func_020aecb8(int *arg0, int *arg1)
{
    int tmp;

    tmp = func_020aefa4((unsigned short *) arg0);
    func_020b00fc(arg0 + 1, arg1, 0x151d, 2, tmp, 0x25, 0);
}

void func_020aec90(char *a, int *b)
{
    func_020b0164(a + 4, b, 4, 0, func_020aef8c((unsigned short *) a), 37, 0);
}

void func_020aec68(int *ptr, int *other)
{
    func_020b0164(ptr + 1, other, 3, 0, func_020aef74((unsigned short *) ptr), 0x25, 0);
}

void func_020aec40(char *a, int *b)
{
    func_020b0164(a + 4, b, 1, 0, func_020aef5c((unsigned short *) a), 0x25, 0);
}

void func_020aebcc(UnkStruct_020aebcc *s, int *counter)
{
    unsigned int i = 0;
    while (i < (unsigned int) func_020aef44((unsigned short *) s)) {
        unsigned int v = s->unk_5A.bits.counter & 0xF;
        unsigned short out;
        if (v < 16) {
            out = (unsigned short) (0x1521 + v);
        } else {
            out = 0x1521;
        }
        s->arr[(*counter)++] = out;
        s->unk_5A.raw =
            (unsigned short) ((s->unk_5A.raw & ~0x1E0) | (((unsigned short) (s->unk_5A.bits.counter + 1) & 0xF) << 5));
        i++;
    }
}

void func_020aeb9c(int *a, int *b)
{
    int v1, v2, v3;
    v1 = func_020aef2c((unsigned short *) a);
    v2 = 0x25;
    v3 = 0;
    func_020b00fc((void *) (a + 1), b, 0x151f, 1, v1, v2, v3);
}

void func_020aeb6c(char *arg0, int *arg1)
{
    int ret_val;
    ret_val = func_020aef28();
    func_020b00fc(arg0 + 4, arg1, 0x155e, 1, ret_val, 0x25, 0);
}

int func_020aea84(void)
{
    void *m;
    void *g;
    void *t;
    void *c;
    u16 buf[2];
    u32 a[2];
    u32 b[2];
    u32 y;
    u32 x;

    if (func_020ad798() == 1) {
        return 0;
    }
    if (func_020af9f0(&data_021f395c) != 0) {
        g = func_020af898(&data_021f395c);
        m = func_0204e414();
        if (m != 0) {
            t = func_0204f694(m, 2);
            if (t != 0) {
                for (y = 0; y < 0x10; y++) {
                    for (x = 0; x < 0x10; x++) {
                        c = func_02037e0c(t, x, y, 0);
                        if (c == 0) {
                            continue;
                        }
                        if (func_0204bba8(c) == 0) {
                            continue;
                        }
                        buf[0] = func_0204bb68(g);
                        func_02037e44(t, buf, x, y, 0);
                        func_020af004(&data_021f395c, g);
                        a[0] = 0;
                        a[1] = 0;
                        if (func_020afc84(a) != 0) {
                            b[0] = 0;
                            b[1] = 0;
                            func_0209e474(b);
                            if (((u8 *) b)[5] == ((u8 *) a)[5] && ((u8 *) b)[4] == ((u8 *) a)[4] &&
                                ((u8 *) b)[3] == ((u8 *) a)[3]) {
                                func_020afcd4();
                            }
                        }
                        func_020afad4(&data_021f395c)->unk_03 = 0;
                        func_020af3a0(&data_021f395c, 1);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
