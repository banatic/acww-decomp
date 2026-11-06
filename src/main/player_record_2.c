/* player_record_2: 65 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02099870 @ 0x02099870, 0xc bytes, Thumb
 * func_0209985c @ 0x0209985c, 0x12 bytes, Thumb
 * func_0209984c @ 0x0209984c, 0x10 bytes, Thumb
 * func_02099834 @ 0x02099834, 0x18 bytes, Thumb
 * func_02099824 @ 0x02099824, 0x10 bytes, Thumb
 * func_02099808 @ 0x02099808, 0x1c bytes, Thumb
 * func_020997f8 @ 0x020997f8, 0x10 bytes, Thumb
 * func_020997e0 @ 0x020997e0, 0x18 bytes, Thumb
 * func_020997d0 @ 0x020997d0, 0x10 bytes, Thumb
 * func_020997b4 @ 0x020997b4, 0x1c bytes, Thumb
 * func_020997a8 @ 0x020997a8, 0xc bytes, Thumb
 * func_02099794 @ 0x02099794, 0x14 bytes, Thumb
 * func_02099784 @ 0x02099784, 0x10 bytes, Thumb
 * func_02099768 @ 0x02099768, 0x1c bytes, Thumb
 * func_0209975c @ 0x0209975c, 0xc bytes, Thumb
 * func_02099740 @ 0x02099740, 0x1c bytes, Thumb
 * func_02099734 @ 0x02099734, 0xc bytes, Thumb
 * func_02099728 @ 0x02099728, 0xc bytes, Thumb
 * func_0209971c @ 0x0209971c, 0xc bytes, Thumb
 * func_02099710 @ 0x02099710, 0xc bytes, Thumb
 * func_02099704 @ 0x02099704, 0xc bytes, Thumb
 * func_020996f8 @ 0x020996f8, 0xc bytes, Thumb
 * func_020996ec @ 0x020996ec, 0xc bytes, Thumb
 * func_020996e0 @ 0x020996e0, 0xc bytes, Thumb
 * func_020996d4 @ 0x020996d4, 0xc bytes, Thumb
 * func_020996c8 @ 0x020996c8, 0xc bytes, Thumb
 * func_020996bc @ 0x020996bc, 0xc bytes, Thumb
 * func_020996b8 @ 0x020996b8, 0x2 bytes, Thumb
 * func_020996ac @ 0x020996ac, 0xc bytes, Thumb
 * func_020996a0 @ 0x020996a0, 0xc bytes, Thumb
 * func_02099694 @ 0x02099694, 0xc bytes, Thumb
 * func_02099688 @ 0x02099688, 0xc bytes, Thumb
 * func_0209967c @ 0x0209967c, 0xc bytes, Thumb
 * func_02099670 @ 0x02099670, 0xc bytes, Thumb
 * func_02099664 @ 0x02099664, 0xc bytes, Thumb
 * func_02099658 @ 0x02099658, 0xc bytes, Thumb
 * func_0209964c @ 0x0209964c, 0xc bytes, Thumb
 * func_02099640 @ 0x02099640, 0xc bytes, Thumb
 * func_0209948c @ 0x0209948c, 0x1b4 bytes, Thumb
 * func_020993b4 @ 0x020993b4, 0xd8 bytes, Thumb
 * func_020993a8 @ 0x020993a8, 0xc bytes, Thumb
 * func_0209939c @ 0x0209939c, 0xc bytes, Thumb
 * func_02099380 @ 0x02099380, 0x1c bytes, Thumb
 * func_02099348 @ 0x02099348, 0x36 bytes, Thumb
 * func_02099314 @ 0x02099314, 0x34 bytes, Thumb
 * func_02099308 @ 0x02099308, 0xc bytes, Thumb
 * func_020992fc @ 0x020992fc, 0xc bytes, Thumb
 * func_020992f0 @ 0x020992f0, 0xc bytes, Thumb
 * func_020992e4 @ 0x020992e4, 0xc bytes, Thumb
 * func_020992d0 @ 0x020992d0, 0x14 bytes, Thumb
 * func_020992c4 @ 0x020992c4, 0xc bytes, Thumb
 * func_020992b8 @ 0x020992b8, 0xc bytes, Thumb
 * func_020992ac @ 0x020992ac, 0xc bytes, Thumb
 * func_020991d4 @ 0x020991d4, 0xd8 bytes, Thumb
 * func_020991c8 @ 0x020991c8, 0xc bytes, Thumb
 * func_020991a0 @ 0x020991a0, 0x28 bytes, Thumb
 * func_02099194 @ 0x02099194, 0xc bytes, Thumb
 * func_02099188 @ 0x02099188, 0xc bytes, Thumb
 * func_02099174 @ 0x02099174, 0x14 bytes, Thumb
 * func_02099164 @ 0x02099164, 0x10 bytes, Thumb
 * func_02099158 @ 0x02099158, 0xc bytes, Thumb
 * func_02099050 @ 0x02099050, 0x108 bytes, Thumb
 * func_02099020 @ 0x02099020, 0x30 bytes, Thumb
 * func_02098ff8 @ 0x02098ff8, 0x28 bytes, Thumb
 * func_02098fd0 @ 0x02098fd0, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x243c];
    unsigned char low_nibble : 4;
} UnkStruct_0209984c;

struct UnkStruct_020997f8 {
    unsigned char pad_00[0x243d];
    unsigned char field : 3;
};

typedef struct {
    unsigned char pad_00[0x243d];
    unsigned char : 3;
    unsigned char field : 3;
} UnkStruct_020997d0;

struct S_99794 {
    unsigned short x;
};

typedef struct {
    unsigned char pad_00[0x2414];
    unsigned short unk_2414;
} UnkStruct_020992c4;

struct LocalInfo {
    u8 pad_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03;
};

typedef struct OA {
    u8 d[0x20];
} OA;

typedef struct OB {
    u8 d[0x20];
} OB;

typedef struct OC {
    u8 d[0x5c];
} OC;

extern int func_02094fec(void *);
extern int func_02099a28(void *);
extern int func_0209a850(int);
extern void func_0209b23c(void *);
extern unsigned short *func_02098f48(int, int);
extern int func_02098e8c(int, int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern void func_02063414(unsigned short *, int, int, int, int, void *, int, int, int, int);
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(unsigned short *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern int func_02098f0c(int, unsigned short *, int, int);
extern int func_0203cd2c(int, unsigned short *, int, int);
extern void *func_0209ad9c(unsigned char *, int);
extern void func_0209b56c(void *);
extern void func_0209af04(unsigned char *);
extern unsigned char *func_02098e44(void *, int);
extern int func_02065ec0(unsigned char *);
extern void func_02066650(unsigned char *);
extern void *func_020987ac(void *p, int x);
extern int data_021dc7bc;
extern int func_02095074(int, int);
extern char data_021dc7a8[];
void *func_020984e8(void);
void func_0209df64(void *);
int func_0209dcdc(struct LocalInfo *, struct LocalInfo *);
void func_020982f8(int);
void func_020981f4(int);
void func_020980f0(int);
void func_02088810(void *);
void func_020889a8(void);
void func_020887f8(void *);
void func_02088ac8(unsigned char *);
void func_0209f100(void *, int);
void func_020882f0(void *);
extern int func_020951bc(int a);
extern int func_02099df4(u8 *p);
extern void *func_02094fd4(OA *o);
extern void *func_020641c8(OB *o);
extern void *func_020a8228(OC *o);
extern int func_0203d7c4(int n, void *o);
extern void func_020a8c1c(void *o);
extern int func_02003618(u8 *p, OA *o);
extern int func_0209c54c(int *q, int i);
extern void *func_020b49d4(OC *o, u8 *q, int t);
extern void func_02064210(u8 *p, OB *o);
extern int func_0207d3dc(void *g, int u, int v, int a, u8 *pb, u8 *pc);
extern void func_02099e18(u8 *p);
extern void *func_020a8210(OC *o);
extern void *func_020641b0(OB *o);
extern void *func_02094fbc(OA *o);
extern int data_020e3128;

int func_02099020(unsigned char *base, unsigned int index);
void func_02098ff8(unsigned int *ptr, unsigned int bit);
void func_02098fd0(unsigned int *ptr, unsigned int bit);

int func_02099870(int r0)
{
    return r0 + 0x247e;
}

int func_0209985c(int argument0)
{
    return func_02094fec((void *) func_02099870((int) argument0));
}

unsigned int func_0209984c(UnkStruct_0209984c *s)
{
    return s->low_nibble;
}

void func_02099834(unsigned char *base, unsigned int value)
{
    base[0x243c] = (unsigned char) ((base[0x243c] & ~0x0f) | (value & 0x0f));
}

unsigned int func_02099824(const unsigned char *ptr)
{
    return ((unsigned int) ptr[0x243c] << 24) >> 28;
}

void func_02099808(unsigned char *base, int val)
{
    unsigned char *p = base + 0x243c;
    *p = (*p & ~0xf0) | ((val & 0xf) << 4);
}

unsigned int func_020997f8(struct UnkStruct_020997f8 *arg)
{
    return arg->field;
}

void func_020997e0(unsigned char *base, int value)
{
    base[0x243d] = (base[0x243d] & ~7) | (value & 7);
}

unsigned int func_020997d0(UnkStruct_020997d0 *p)
{
    return p->field;
}

void func_020997b4(unsigned char *data, int value)
{
    unsigned char *p = data + 0x243d;
    *p = (*p & ~0x38) | ((value & 7) << 3);
}

short func_020997a8(char *arg0)
{
    return *(short *) (arg0 + 0x2412);
}

void func_02099794(char *p0, struct S_99794 v)
{
    *(unsigned short *) (p0 + 0x2412) = v.x;
}

unsigned int func_02099784(unsigned char *ptr)
{
    return ((unsigned int) ptr[0x243d] << 24) >> 30;
}

void func_02099768(unsigned char *array, int val)
{
    unsigned char *p = array + 0x243d;
    *p = (*p & ~0xc0) | ((val & 3) << 6);
}

int func_0209975c(int a)
{
    return func_02099020((unsigned char *) a, 0);
}

void func_02099740(int r0, int r1)
{
    if (r1 != 0) {
        func_02098ff8((unsigned int *) r0, 0);
    } else {
        func_02098fd0((unsigned int *) r0, 0);
    }
}

int func_02099734(int a)
{
    return a + 0x11A8;
}

unsigned int func_02099728(unsigned int arg0)
{
    return arg0 + 0x2406;
}

void func_0209971c(unsigned short *r0, unsigned short *r1)
{
    unsigned short value;
    value = *r1;
    *(unsigned short *) ((unsigned char *) r0 + 0x2406) = value;
}

unsigned int func_02099710(unsigned int r0)
{
    return r0 + 0x2408;
}

void func_02099704(unsigned short *r0, unsigned short *r1)
{
    unsigned short value;
    value = *r1;
    *(unsigned short *) ((char *) r0 + 0x2408) = value;
}

int func_020996f8(int arg)
{
    return arg + 0x240a;
}

void func_020996ec(unsigned char *dest, unsigned short *src)
{
    *(unsigned short *) (dest + 0x240a) = *src;
}

int func_020996e0(int a)
{
    return a + 0x240c;
}

void func_020996d4(unsigned short *dst_base, unsigned short *src)
{
    *(unsigned short *) ((char *) dst_base + 0x240c) = *src;
}

int func_020996c8(int a)
{
    return a + 0x240e;
}

void func_020996bc(unsigned short *r0, unsigned short *r1)
{
    unsigned short value;
    value = *r1;
    *(unsigned short *) ((char *) r0 + 0x240e) = value;
}

void *func_020996b8(void *object)
{
    return object;
}

int func_020996ac(int a)
{
    return a + 0x1c18;
}

unsigned int func_020996a0(unsigned int r0)
{
    return r0 + 0x2404;
}

int func_02099694(int r0)
{
    return r0 + 0x2427;
}

unsigned int func_02099688(unsigned int arg0)
{
    return arg0 + 0x242c;
}

int func_0209967c(int a)
{
    return a + 0x23ec;
}

int func_02099670(int arg)
{
    return arg + 0x2416;
}

int func_02099664(int x)
{
    return x + 0x1f0c;
}

int func_02099658(int a)
{
    return a + 0x1f5c;
}

int func_0209964c(int r0)
{
    return r0 + 0x1d3b;
}

int func_02099640(int a)
{
    return a + 0x1e40;
}

void func_0209948c(void *self)
{
    unsigned short w[6];
    int o[2][2];
    int a;
    int i;
    unsigned short *p;
    int t;
    unsigned int ok;

    if (func_02099a28(self) == 0) {
        return;
    }
    w[0] = 0xfff1;
    func_0209b23c((void *) func_0209a850((int) func_02099640((int) self)));
    a = func_02099734((int) self);
    p = func_02098f48(a, 0);

    for (i = 0; i < 0xf; p++, i++) {
        ok = 0;
        if (*p >= 0x155f && *p <= 0x1560) {
            ok = 1;
        }
        if (ok == 0) {
            continue;
        }
        if (func_02098e8c(a, i) != 2) {
            continue;
        }

        w[0] = 0xfff1;
        if (func_0204bcdc(p) != 0) {
            w[5] = 0x1560;
            t = func_0204bc64(p);
            ok = (t == func_0204bc64(&w[5])) ? 1 : 0;
        } else {
            if (*p == 0x1560) {
                ok = 1;
            } else {
                ok = 0;
            }
        }

        if (ok != 0) {
            func_02063414(&w[1], 0x1100, 0x44, 0, 0, self, 1, 10, 0, 1);
            w[0] = w[1];
            if (w[0] == 0xfff1) {
                func_02063ccc(o[0], 4, 0);
                func_020638d4(&w[2], o[0], 0, 0, 1, 1, 0);
                w[0] = w[2];
                func_02063cc8(o[0]);
            }
        } else {
            func_02063414(&w[3], 0x1144, 0x44, 0, 0, self, 1, 10, 0, 1);
            w[0] = w[3];
            if (w[0] == 0xfff1) {
                func_02063ccc(o[1], 3, 0);
                func_020638d4(&w[4], o[1], 0, 0, 1, 1, 0);
                w[0] = w[4];
                func_02063cc8(o[1]);
            }
        }

        func_02098f0c(a, &w[0], i, 0);
        if (w[0] != 0xfff1) {
            func_0203cd2c(func_020996ac((int) self), &w[0], 0, 1);
        }
    }
}

void func_020993b4(void *param)
{
    void *p1;
    unsigned char *p2;
    int i;

    if (func_02099a28(param) == 0) {
        return;
    }

    p1 = (void *) func_02099734((int) param);
    p2 = (unsigned char *) func_02098f48((int) p1, 0);

    func_0209b56c((void *) func_0209ad9c((unsigned char *) func_02099640((int) param), 0));
    func_0209b56c((void *) func_0209ad9c((unsigned char *) func_02099640((int) param), 1));
    func_0209af04((unsigned char *) func_02099640((int) param) + 0xa4);

    {
        int val2 = 0;
        int val3 = 0;

        for (i = 0; i < 15; i++) {
            if (func_02098e8c((int) p1, i) == 2) {
                int cond = val2;
                unsigned short val = *(unsigned short *) p2;
                if ((unsigned int) val >= 0x11a8u && (unsigned int) val <= 0x12a7u) {
                    cond = 1;
                }
                if (cond) {
                    func_02098f0c((int) p1, (unsigned short *) p2, i, 1);
                    func_0203cd2c((unsigned int) (unsigned char *) func_020996ac((int) param), (unsigned short *) p2,
                                  (unsigned int) val3, 1);
                }
            }
            p2 += 2;
        }
    }

    p2 = func_02098e44(p1, 0);
    for (i = 0; i < 10; i++) {
        if ((unsigned char) (func_02065ec0(p2) + 0xf9) <= 1) {
            func_02066650(p2);
        }
        p2 += 0x100;
    }
}

unsigned int func_020993a8(unsigned int r0)
{
    return r0 + 0x2410;
}

void func_0209939c(unsigned short *r0, unsigned short *r1)
{
    unsigned short value;
    value = *r1;
    *(unsigned short *) ((unsigned char *) r0 + 0x2410) = value;
}

void *func_02099380(int argument0)
{
    return func_020987ac(&data_021dc7bc, func_02099870((int) argument0));
}

int func_02099348(int param1, int param2)
{
    int r;
    int v0;
    int v1;

    v0 = func_02099870(param1);
    r = 0;
    if (func_02094fec((void *) v0) != -1) {
        v1 = (int) func_02099380(param1);
        if (v1 != 0) {
            func_02095074(func_02099870(v1), param2);
            r = 1;
        }
    }
    return r;
}

int func_02099314(void *ptr, int count)
{
    int i = 0;
    int result = -1;
    void *p = ptr;

    while (i < count) {
        if (func_02099a28(p) == 0) {
            result = i;
            break;
        }
        p = (char *) p + 0x249c;
        i++;
    }
    return result;
}

unsigned int func_02099308(unsigned int r0)
{
    return r0 + 0x2400;
}

int func_020992fc(int arg0)
{
    return arg0 + 0x23e0;
}

unsigned int func_020992f0(unsigned int r0)
{
    return r0 + 0x23e8;
}

int func_020992e4(int a)
{
    return a + 0x2414;
}

void func_020992d0(unsigned char *r0, unsigned char r1, unsigned char r2)
{
    r0[0x2415] = r1;
    r0[0x2414] = r2;
}

void func_020992c4(UnkStruct_020992c4 *s)
{
    s->unk_2414 = 0;
}

unsigned char *func_020992b8(unsigned char *r0, unsigned char r1)
{
    r0[0x2453] = r1;
    return r0;
}

unsigned char func_020992ac(unsigned char *param0)
{
    return param0[0x2453];
}

void func_020991d4(void)
{
    struct LocalInfo local;
    char *base;
    void *self;
    struct LocalInfo *p6;
    int r4;

    base = (char *) &data_021dc7a8;
    self = func_020984e8();
    if (self == 0) {
        return;
    }

    func_0209df64(&local);
    p6 = (struct LocalInfo *) func_02099308((unsigned int) self);
    r4 = func_0209dcdc(&local, p6);

    func_020982f8((local.unk_01 - p6->unk_01) + 12 * (local.unk_02 - p6->unk_02));

    func_020981f4(r4);
    func_020980f0(r4);
    func_02088810((void *) func_02099670((int) self));
    func_02099670((int) self);
    func_020889a8();

    if (r4 != 0) {
        func_0209948c(self);
    }

    if (local.unk_02 != (int) func_020992ac((unsigned char *) self)) {
        func_020992b8((unsigned char *) self, 0xff);
    }

    if (r4 != 0) {
        func_020887f8((void *) func_0209967c((int) self));
        func_02099768((unsigned char *) self, 0);
        func_02088ac8((unsigned char *) func_02099670((int) self));
        func_0209f100(&data_021dc7a8, 0x10);
    }

    if (r4 < 0) {
        func_020882f0((void *) func_02099688((unsigned int) self));
        func_020882f0(base + 0x173e2);
    }

    func_0209df64((struct LocalInfo *) func_02099308((unsigned int) self));
}

unsigned char func_020991c8(unsigned char *param0)
{
    return param0[0x2451];
}

void func_020991a0(unsigned char *p)
{
    p[0x2451] = p[0x2451] + 1;
    if (p[0x2451] == 1) {
        p[0x2451] = 2;
    }
    if (p[0x2451] > 10) {
        p[0x2451] = 10;
    }
}

unsigned char func_02099194(const unsigned char *base)
{
    return base[0x2452];
}

void func_02099188(unsigned char *ptr, unsigned char value)
{
    ptr[0x2452] = value;
}

unsigned char func_02099174(unsigned char *base, unsigned int index)
{
    if (index < 8) {
        return (base + index)[0x2454];
    }
    return 0xff;
}

void func_02099164(char *base, unsigned int index, char value)
{
    if (index < 8) {
        (base + index)[0x2454] = value;
    }
}

unsigned int func_02099158(unsigned int arg0)
{
    return arg0 + 0x245c;
}

void func_02099050(u8 *p)
{
    int a;
    int u;
    u8 *pc;
    int t;
    u8 bv;
    int w;
    OA oa;
    OB ob;
    OC oc;
    u8 *pb;
    int v;
    int i;

    a = func_02099870((int) p);
    if (func_020951bc(a)) {
        if (func_02099df4(p + 0x245c)) {
            pb = p + 0x246a;
            pc = p + 0x247a;
            func_02094fd4(&oa);
            func_020641c8(&ob);
            func_020a8228(&oc);
            u = 0;
            v = 10;
            w = 0;
            if (*(u16 *) (p + 0x247a) != 0xfff1) {
                u = v;
                v = 5;
            }
            func_02095074(a, (int) (&oa));
            func_0203d7c4(0, &oa);
            func_020a8c1c(&oa);
            func_02003618(pb, &oa);
            func_0203d7c4(1, &oa);
            for (i = 0; i < 6; i++) {
                t = func_0209c54c(&w, i);
                func_020a8c1c(&oc);
                bv = (u8) w;
                func_020b49d4(&oc, &bv, t);
                func_0203d7c4(i + 2, &oc);
            }
            func_02064210(p + 0x245c, &ob);
            func_0203d7c4(8, &ob);
            if (func_0207d3dc(&data_020e3128, u, v, a, pb, pc)) {
                func_02099e18(p + 0x245c);
            }
            func_020a8210(&oc);
            func_020641b0(&ob);
            func_02094fbc(&oa);
        }
    }
}

int func_02099020(unsigned char *base, unsigned int index)
{
    int high = (int) (index >> 5);
    int low = index & 0x1f;
    int result;
    if (high >= 2) {
        goto zero;
    }
    result = 1;
    if ((1 << low) & *(unsigned int *) (base + high * 4 + 0x23f8)) {
        goto end;
    }
zero:
    result = 0;
end:
    return result;
}

void func_02098ff8(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    word = bit >> 5;
    shift = bit & 0x1f;
    if ((int) word < 2) {
        unsigned int *base = (unsigned int *) ((char *) ptr + 0x23f8);
        ((volatile unsigned int *) base)[word] = (1 << shift) | ((volatile unsigned int *) base)[word];
    }
}

void func_02098fd0(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    word = bit >> 5;
    shift = bit & 0x1f;
    if ((int) word < 2) {
        unsigned int *base = (unsigned int *) ((char *) ptr + 0x23f8);
        base[word] = ~(1 << shift) & ((volatile unsigned int *) base)[word];
    }
}
