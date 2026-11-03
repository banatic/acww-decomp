/* fox_shop: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ae494 @ 0x020ae494, 0x34 bytes, Thumb
 * func_020ae470 @ 0x020ae470, 0x24 bytes, Thumb
 * func_020ae458 @ 0x020ae458, 0x16 bytes, Thumb
 * func_020ae440 @ 0x020ae440, 0x16 bytes, Thumb
 * func_020ae410 @ 0x020ae410, 0x30 bytes, Thumb
 * func_020ae3ec @ 0x020ae3ec, 0x24 bytes, Thumb
 * func_020ae3d4 @ 0x020ae3d4, 0x16 bytes, Thumb
 * func_020ae3c4 @ 0x020ae3c4, 0x10 bytes, Thumb
 * func_020ae3bc @ 0x020ae3bc, 0x8 bytes, Thumb
 * func_020ae3b8 @ 0x020ae3b8, 0x4 bytes, Thumb
 * func_020ae32c @ 0x020ae32c, 0x8c bytes, Thumb
 * func_020ae310 @ 0x020ae310, 0x1c bytes, Thumb
 * func_020ae2c4 @ 0x020ae2c4, 0x4c bytes, Thumb
 * func_020ae270 @ 0x020ae270, 0x54 bytes, Thumb
 * func_020ae190 @ 0x020ae190, 0xe0 bytes, Thumb
 * func_020ae03c @ 0x020ae03c, 0x154 bytes, Thumb
 * func_020ae02c @ 0x020ae02c, 0x10 bytes, Thumb
 * func_020adfc0 @ 0x020adfc0, 0x6c bytes, Thumb
 * func_020adfa4 @ 0x020adfa4, 0x1c bytes, Thumb
 * func_020adf8c @ 0x020adf8c, 0x18 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

typedef struct {
    u16 tag;
} UnkStruct_020adfc0;

struct UnkStruct_020adf8c {
    char pad_00[0x10];
    char unk_10;
};

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_02094ffc(void *);
extern unsigned char data_021f49e8;
extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern int func_020ae724(void *ptr);
extern void func_020ae720(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020ae6fc(void *);
extern void func_020b00c8(void *p1, void *p2, int n);
extern int data_021f49fc;
extern unsigned short data_021f49f8;
extern int data_021f4a14;
extern int func_0204e414(void);
extern void *func_0204f694(int a, int b);
extern void __register_global_object(void *, void *, void *);
extern int func_02037da8(void *a, void *b, void *c, void *d, void *e, int f);
extern void func_0209e474(void *);
extern void func_020ae4fc(int a, unsigned char b);
extern int func_020ae4c8(void);
extern int func_0209871c(int *a, int b);
extern int func_020ae538(int a, int b);
extern void func_020ae514(int, int);
extern unsigned char data_021dc7bc[];
extern unsigned char data_021f3b30[];
extern void *data_020ccf94;
extern int func_020ae67c(void *);
extern int func_020ae590(signed char *);
extern int func_02073d90(void *);
extern void func_02066694(void *);
extern int func_020644cc(int);
extern void *func_020ae774(void *);
extern int func_020ae5bc(int, void *);
extern int func_0203d7c4(int, void *);
extern void *func_02098844(unsigned int, int);
extern int func_02099a28(unsigned int);
extern int func_02099020(void *, int);
extern void func_02066024(void *, void *, void *, void *, void *, void *);
extern int func_02097a54(void *);
extern int func_020979f0(void *, int);
extern void func_020ae56c(void *);
extern void *func_020ae75c(void *);
extern void func_02066688(void *);
extern unsigned char data_020e4160[];
extern unsigned char data_020e4164[];
extern unsigned char data_020e419c[];
extern unsigned int func_0205be44(void);
extern void func_02063ccc(void *p, int c, unsigned int n);
extern void func_020638d4(void *dest, void *src, int a, int b, int c, unsigned int d, int e);
extern void func_02063cc8(void *p);
extern unsigned int func_0205be20(void);
extern unsigned int func_0205be2c(void);
extern const unsigned char data_020d1e48[];
extern int func_020b0074(void *p1, int p2, void *p3);
extern int func_0204bcdc(void *p);
extern void *func_0204bc64(void *p);
extern void *func_020b0038(int, int, int, int, int);
extern int func_020aff84(int, void *, void *, int);

unsigned int func_020ae458(unsigned int *param1, unsigned int param2);
void func_020ae3c4(void *arg);
void *func_020adfa4(int a, int b, int c);

int func_020ae494(signed char *param)
{
    if (param[4] != -1) {
        if (func_02094ffc((void *) func_02099870((int) func_020984e8())) == 1) {
            data_021f49e8 = 1;
            return 1;
        }
    }
    return 0;
}

int func_020ae470(void *param)
{
    unsigned int count = 0;
    unsigned int i = count;

    do {
        if ((int) func_020ae458((unsigned int *) param, i) == 0) {
            count++;
        }
        i++;
    } while (i < 32);

    return count;
}

unsigned int func_020ae458(unsigned int *param1, unsigned int param2)
{
    unsigned int r3;
    unsigned int r2;
    unsigned int r1;
    unsigned int r0;

    r3 = *param1;
    r0 = 1;
    r2 = 0x1f;
    r1 = param2 & r2;
    r2 = r0 << r1;
    r3 = r3 & r2;
    if (r3 != 0) {
        r0 = 1;
    } else {
        r0 = 0;
    }
    return r0;
}

void func_020ae440(void *r0, int r1)
{
    unsigned int r4 = *(unsigned int *) r0;
    unsigned int r3 = 1;
    r3 <<= (r1 & 0x1f);
    r4 |= r3;
    *(unsigned int *) r0 = r4;
}

void *func_020ae410(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 3, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_020ae724((char *) arg + 8);
    return arg;
}

void *func_020ae3ec(void *p)
{
    func_020ae720((char *) p + 8);
    __cxa_vec_cleanup((void *) (p), 3, 2, (void (*)(void *)) func_020051b0);
    return p;
}

void func_020ae3d4(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020ae3c4(r4);
    r4 = (char *) r4 + 8;
    func_020ae6fc(r4);
}

void func_020ae3c4(void *arg)
{
    func_020b00c8(arg, (char *) arg + 0x10, 3);
}

void func_020ae3bc(void *argument0)
{
    func_020ae3d4((void *) argument0);
}

int func_020ae3b8(int p0)
{
    return ((int) (p0) + (8));
}

int func_020ae32c(void)
{
    int v1;
    int v2;
    Pair y;
    void *h;
    int t;

    t = func_0204e414();
    if (t != 0) {
        h = func_0204f694(t, 0x200);
        if (h != 0) {
            if ((data_021f49fc & 1) == 0) {
                data_021f49f8 = 0x5012;
                __register_global_object((void *) (&data_021f49f8), (((void *) func_020051b0)), (void *) (&data_021f4a14));
                data_021f49fc |= 1;
            }
            if (func_02037da8(h, &v1, &v2, &data_021f49f8, &data_021f49f8, 0) != 0) {
                y.unk_00 = 0;
                y.w1 = 0;
                func_0209e474(&y);
                if (((unsigned char *) &y)[2] >= 6) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void func_020ae310(int param)
{
    func_020ae4fc(func_020ae3b8((int) (((int *) data_021f3b30))), (unsigned char) param);
}

int func_020ae2c4(void)
{
    int p;

    p = func_020984e8();
    if (p != 0) {
        p = func_02099870(p);
        if (func_02094ffc((void *) p) == 1) {
            return func_020ae4c8();
        }
        p = (unsigned char) (func_0209871c(((int *) data_021dc7bc), p) & 3);
        return func_020ae538(func_020ae3b8((int) (((int *) data_021f3b30))), p);
    } else {
        return 0;
    }
}

int func_020ae270(void)
{
    int tested_value0;
    if ((tested_value0 = (int) (func_020984e8())) != 0) {
        int v = func_02099870(tested_value0);
        if (func_02094ffc((void *) v) == 1) {
            return func_020ae494((signed char *) func_020ae3b8((int) ((void *) data_021f3b30)));
        } else {
            v = (unsigned char) (func_0209871c((int *) ((void *) data_021dc7bc), v) & 3);
            func_020ae514(func_020ae3b8((int) ((void *) data_021f3b30)), v);
            return 1;
        }
    }
    return 0;
}

void func_020ae190(void)
{
    struct {
        char c;
        char pad1[0x3];
        char b0[0x34];
        char b1[0x104];
    } locals;
    int i;
    int zero;

    func_020ae67c((void *) func_020ae3b8((unsigned int) data_021f3b30));
    if (func_020ae590((signed char *) func_020ae3b8((unsigned int) data_021f3b30)) == 0) {
        return;
    }
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }

    func_02066694(locals.b1);
    locals.c = (char) func_020644cc(3);
    func_020ae774(locals.b0);
    func_020ae5bc(func_020ae3b8((unsigned int) data_021f3b30), locals.b0);
    func_0203d7c4(2, locals.b0);

    zero = 0;
    for (i = 0; i < 4; i++) {
        void *obj;
        void *ret;

        obj = func_02098844((unsigned int) data_021dc7bc, i);
        if (obj == 0) {
            continue;
        }
        if (func_02099a28((unsigned int) obj) == 0) {
            continue;
        }
        if (func_02099020(obj, 0xc) == 0) {
            continue;
        }
        ret = (void *) func_02099870((int) obj);
        func_02066024(locals.b1, &locals.c, (void *) data_020e419c, (void *) data_020e4160, (void *) data_020e4164, ret);
        if (func_02097a54(locals.b1) != 0) {
            continue;
        }
        func_020979f0(locals.b1, zero);
    }

    func_020ae56c((void *) func_020ae3b8((unsigned int) data_021f3b30));
    func_020ae75c(locals.b0);
    func_02066688(locals.b1);
}

void func_020ae03c(unsigned short *out)
{
    unsigned int one = 1;
    unsigned char buf[0x34];
    unsigned int i, r;
    unsigned int t1, t2;
    const unsigned char *p;

    func_020ae3c4(out);

    t1 = func_0205be44() / 10 + 0x32;

    if ((unsigned int) func_020644cc(100) < t1) {
        func_02063ccc(buf + 0x10, 0, 0x26);
        func_020638d4(buf, buf + 0x10, 0, 0, 0, one, 0);
        *out = *(unsigned short *) buf;
        func_02063cc8(buf + 0x10);
    } else {
        func_02063ccc(buf + 0x18, 0, 0x27);
        func_020638d4(buf + 2, buf + 0x18, 0, 0, 0, one, 0);
        *out = *(unsigned short *) (buf + 2);
        func_02063cc8(buf + 0x18);
    }

    t2 = (int) (func_0205be20() + func_0205be2c()) / 10 + 0x32;

    for (i = 1; i < 3; i++) {
        if ((unsigned int) func_020644cc(100) < t2) {
            func_02063ccc(buf + 0x20, 0, 5);
            func_020638d4(buf + 4, buf + 0x20, 0, 0, 0, one, 0);
            out[i] = *(unsigned short *) (buf + 4);
            func_02063cc8(buf + 0x20);
        } else {
            func_02063ccc(buf + 0x28, 0, 0);
            func_020638d4(buf + 6, buf + 0x28, 0, 0, 0, one, 0);
            out[i] = *(unsigned short *) (buf + 6);
            func_02063cc8(buf + 0x28);
        }
    }

    *(unsigned short *) (buf + 8) = 0xfff1;
    *(unsigned short *) (buf + 10) = 0xfff1;
    *(unsigned short *) (buf + 12) = 0xfff1;

    for (i = 0; i < 3; i++) {
        ((unsigned short *) (buf + 8))[i] = out[i];
    }

    r = (unsigned int) func_020644cc(6);
    for (i = 0, p = &data_020d1e48[3 * r]; i < 3; i++) {
        out[i] = ((unsigned short *) (buf + 8))[p[i]];
    }
}

int func_020ae02c(void *a, void *b)
{
    return func_020b0074(b, 3, (char *) a + 16);
}

static __inline int EqA(void *p, void *q)
{
    if (func_0204bc64(p) == func_0204bc64(q)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 x, u16 y)
{
    if (x == y) {
        return 1;
    }
    return 0;
}

int func_020adfc0(UnkStruct_020adfc0 *a, UnkStruct_020adfc0 *b)
{
    unsigned int i;
    UnkStruct_020adfc0 *p;
    int result;

    for (i = 0; i < 3; i++) {
        p = (UnkStruct_020adfc0 *) func_020adfa4((int) a, i, 0);
        if (func_0204bcdc(p)) {
            result = EqA(p, b);
        } else {
            result = EqB(p->tag, b->tag);
        }
        if (result != 0) {
            return func_020ae02c((void *) a, (void *) i);
        }
    }
    return 0;
}

void *func_020adfa4(int a, int b, int c)
{
    return func_020b0038(b, a, a + 16, 3, c);
}

int func_020adf8c(struct UnkStruct_020adf8c *a, int b)
{
    return func_020aff84(b, a, &a->unk_10, 3);
}
