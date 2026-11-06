/* villager_mode: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207dc30 @ 0x0207dc30, 0x78 bytes, Thumb
 * func_0207dbe8 @ 0x0207dbe8, 0x48 bytes, Thumb
 * func_0207db48 @ 0x0207db48, 0xa0 bytes, Thumb
 * func_0207daf4 @ 0x0207daf4, 0x52 bytes, Thumb
 * func_0207dac8 @ 0x0207dac8, 0x2c bytes, Thumb
 * func_0207d9d4 @ 0x0207d9d4, 0xf4 bytes, Thumb
 * func_0207d978 @ 0x0207d978, 0x5a bytes, Thumb
 * func_0207d91c @ 0x0207d91c, 0x5a bytes, Thumb
 * func_0207d840 @ 0x0207d840, 0xdc bytes, Thumb
 * func_0207d788 @ 0x0207d788, 0xb8 bytes, Thumb
 * func_0207d71c @ 0x0207d71c, 0x6a bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 w1;
} UnkStruct_0207db48;

extern int func_02003704(int);
extern void *func_0207f1c8(void *);
extern void *func_0209b5ec(void *);
extern void func_0209c32c(void *, int);
extern void func_0209baf4(void *);
extern unsigned int func_0208150c(unsigned int);
extern void *func_0209bfec(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0209b5e8(int);
extern void *func_020036e8(void *p);
extern void *func_0208222c(void *p);
extern int func_0209dffc(void *p);
extern void func_0209e29c(void *tmp, int flag);
extern int func_0209e3ac(void *list, void *tmp, int size);
extern int func_02080814(int);
extern void func_0209beb0(int, int, int);
extern void func_0209bee8(int, int, int);
extern int func_0209c380(void *a);
extern void *func_0209bfe8(void *a);
extern int func_0209e350(void *a, void *b);
extern int func_0209c1c0(void *a, void *b);
extern int func_0209bf28(void *a, void *b);
extern void func_0209bf80(void *a, void *b);
extern int func_0209c370(int);
extern int func_0209c330(int);
extern int func_0209c2c0(int);
extern int func_0209c108(int);
extern int func_0209c168(int);
extern int func_0209c38c(int);
extern int func_0207f270(int);
extern int func_020794d0(int);
extern void func_0209bd5c(int);
extern int func_0209c310(int);
extern void func_0209bd30(int, int, short *, int);
extern void func_0207f414(int, int, int);
extern int func_0209c0a0(int h, s64 *d);
extern int func_0209c020(int h, s64 *d);
extern void *func_0209b91c(void *);
extern int func_0209bd44(void *);
extern int func_0209bd04(void *);
extern int func_0209bba0(void *);
extern int func_0209bc40(void *);
extern void func_0207dcf4(void *);
extern void func_0209c270(unsigned char *);

void func_0207dc30(void *a, void *b)
{
    void *p;

    if (func_02003704((int) func_0208150c((unsigned int) a)) == 0) {
        return;
    }

    p = (func_0209b5ec((void *) func_0207f1c8(a)));

    if (func_0209c330((int) p) == 2 || (func_0209c330((int) p) == 8 && func_0209c2c0((int) p) != 0)) {
        ((unsigned char *) p)[0x21] = (unsigned char) ((((unsigned char *) p)[0x21] & ~1) | 1);
    }

    func_0209c32c(p, 9);
    MI_CpuCopy8((void *) b, (void *) ((const void *) func_0209bfec(p)), 8);
    func_0209baf4((void *) func_0209b5e8((int) (func_0207f1c8(a))));
}

void func_0207dbe8(void *p1, void *p2)
{
    void *v;
    void *r;

    if (func_02003704((int) ((void *) func_0208150c((unsigned int) p1)))) {
        v = func_0209b5ec((void *) (unsigned int) func_0207f1c8(p1));
        func_0209c32c(v, 0xa);
        r = func_0209bfec(v);
        MI_CpuCopy8(p2, r, 8);
        func_0209baf4((void *) func_0209b5e8((int) (unsigned int) func_0207f1c8(p1)));
    }
}

int func_0207db48(void *self, void *list)
{
    void *b;
    void *a;
    UnkStruct_0207db48 tmp;
    int result;

    b = (void *) func_0208150c((unsigned int) self);
    a = (func_0209b5ec((void *) func_0207f1c8(self)));

    if (func_02003704((int) b) == 0) {
        goto fail;
    }
    if (func_0209c370((int) a) == 0) {
        goto fail;
    }

    b = func_0208222c(func_020036e8(b));
    a = func_0209bfec(a);
    if (func_0209dffc(a) != 0) {
        goto fail;
    }

    tmp.unk_00 = 0;
    tmp.w1 = 0;
    MI_CpuCopy8((void *) a, &tmp, 8);
    ((u8 *) &tmp)[2] = ((u8 *) b)[2];
    ((u8 *) &tmp)[1] = ((u8 *) b)[3];

    if (((u8 *) a)[2] > ((u8 *) b)[2] || (((u8 *) b)[2] == ((u8 *) a)[2] && ((u8 *) b)[3] == ((u8 *) a)[1])) {
        func_0209e29c(&tmp, 1);
    }

    result = func_0209e3ac(list, &tmp, 0x3e) == 1 ? 1 : 0;
    return result;

fail:
    return 0;
}

void func_0207daf4(int arg0, int arg1)
{
    int tmp;

    if (func_02003704((int) func_0208150c(arg0)) && func_02003704((int) func_0208150c(arg1)) && (tmp = func_02080814(arg0))) {
        func_0209beb0((int) func_0209b5ec((void *) ((int) func_0207f1c8((void *) arg0))),
                      (int) func_0209b5ec((void *) ((int) func_0207f1c8((void *) arg1))), tmp);
    }
}

void func_0207dac8(int arg1, int arg2, int arg3)
{
    if (func_02003704((int) ((void *) func_0208150c(arg1))) != 0) {
        func_0209bee8((int) func_0209b5ec((void *) (unsigned int) func_0207f1c8((void *) arg1)), arg2, arg3);
    }
}

void func_0207d9d4(void *self, void *a)
{
    void *r5, *r6, *r7;
    int limit, val, d, loop;
    u32 local[2];

    r5 = func_0209b5ec((void *) (unsigned int) func_0207f1c8(self));

    if (func_02003704((int) func_0208150c((unsigned int) self)) == 0) {
        return;
    }
    if (func_0209c370((int) r5) == 0) {
        return;
    }
    if (func_0209c380(r5) == 0) {
        return;
    }

    r6 = func_0209bfe8(r5);
    r7 = (void *) func_02080814((int) self);

    if (func_0209dffc(r6) != 0) {
        return;
    }
    if (r7 == 0) {
        return;
    }

    d = func_0209e350(r6, a);
    if (d < 0) {
        d = -d;
    }
    limit = d / 0x5a0;
    if (limit <= 0) {
        return;
    }

    if (func_0209c1c0(r5, a) != 0) {
        local[0] = 0;
        local[1] = 0;
        loop = limit;

        MI_CpuCopy8(func_0209bfec(r5), local, 8);

        d = func_0209e350(local, r6);
        if (d < 0) {
            d = -d;
        }
        val = d / 0x5a0;

        if (val < 7) {
            func_0209e29c(local, 6);
            d = func_0209e350(local, a);
            if (d < 0) {
                d = -d;
            }
            loop = d / 0x5a0;
        }

        while (loop > 0) {
            if (func_0209bf28(r5, r7) == 0) {
                break;
            }
            loop--;
        }

        func_0209bf80(r5, r7);
    }

    func_0209e29c(r6, limit);
}

void func_0207d978(unsigned int param0, unsigned int param1)
{
    int v;
    v = ((int) func_0209b5ec((void *) (int) func_0207f1c8((void *) param0)));
    if (func_02003704((int) func_0208150c(param0)) == 0) {
        return;
    }
    if (func_0209c370(v) == 0) {
        return;
    }
    v = (int) func_0209bfec((void *) v);
    if (func_0209dffc((void *) v) == 0 && func_0209e3ac((void *) param1, (void *) v, 0x3f) != -1) {
        return;
    }
    MI_CpuCopy8((void *) param1, (void *) v, 8);
}

void func_0207d91c(unsigned int a, unsigned int b)
{
    unsigned int r4;

    r4 = (unsigned int) func_0209b5ec((void *) (unsigned int) func_0207f1c8((void *) a));
    if (func_02003704((int) ((void *) func_0208150c(a))) == 0) {
        return;
    }
    if (func_0209c370(r4) == 0) {
        return;
    }
    r4 = (unsigned int) func_0209bfe8((void *) r4);
    if (func_0209dffc((void *) ((const unsigned char *) r4)) != 0 || func_0209e3ac((void *) b, (void *) r4, 0x3f) == -1) {
        MI_CpuCopy8((void *) b, (void *) r4, 8);
    }
}

int func_0207d840(int param0, int param1)
{
    int var_b;
    int var_a;
    int r4, r6, r7;
    unsigned short sh;

    var_a = (int) func_0208150c(param0);
    r6 = ((int) func_0209b5ec((void *) (int) func_0207f1c8((void *) param0)));
    r4 = 12;
    r7 = func_0209c330(r6);

    if (func_02003704(var_a) == 0) {
        goto exit;
    }
    if (func_0209c370(r6) == 0) {
        goto exit;
    }

    var_b = func_0209c2c0(r6);

    if (func_0209c330(r6) == 8) {
        if (func_0207db48((void *) param0, (void *) param1)) {
            r4 = func_0209c108(r6);
        }
    } else {
        func_0207d9d4((void *) param0, (void *) param1);
        r4 = func_0209c168(r6);
    }

    if (r4 == 12) {
        goto exit;
    }
    if (func_0209c38c(r7) && r7 == r4) {
        goto exit;
    }

    func_0209baf4((void *) (func_0209b5e8((int) func_0207f1c8((void *) param0))));
    r6 = func_020794d0(func_0207f270(param0));
    func_0209bd5c(r6);

    if (func_0209c310(r4) == 0) {
        sh = 0xfff1;
        func_0209bd30(r6, r4, (short *) &sh, 0);
    }

    if (func_0209c38c(r4) != 0) {
        func_0207f414(param0, r4, var_b);
    }
exit:
    return r4;
}

int func_0207d788(void *a, s64 *b, s64 *c, s64 *d)
{
    // DECLS
    int t;
    int e;
    int ret;
    int h;
    // ENDDECLS

    t = (int) func_0208150c((unsigned int) a);
    h = ((int) func_0209b5ec((void *) (int) func_0207f1c8(a)));
    ret = 0xc;
    e = func_0209c2c0(h);
    if (func_02003704(t)) {
        if (func_0209c370(h)) {
            switch (func_0209c330(h)) {
                case 0xb:
                    ret = func_0209c0a0(h, d);
                    if (ret != 0xc) {
                        func_0207f414((int) a, ret, e);
                    }
                    if (ret != 0xc) {
                        MI_CpuCopy8(d, b, 8);
                        if (*c != 0) {
                            MI_CpuCopy8(d, c, 8);
                        }
                    }
                    break;
                case 0xa:
                    ret = func_0209c020(h, d);
                    if (ret != 0xc) {
                        func_0207f414((int) a, ret, e);
                    }
                    break;
                default:
                    ret = func_0207d840((int) a, (int) d);
                    break;
            }
        }
    }
    return ret;
}

void func_0207d71c(void *p)
{
    void *r6;
    void *r7;
    void *r4;

    if (func_02003704((int) ((void *) func_0208150c((unsigned int) p))) != 0) {
        r6 = func_0207f1c8(p);
        r7 = (void *) func_0209b5e8((int) r6);
        r4 = func_0209b91c((void *) r7);
        if (func_0209bd44(r4) != 0) {
            if (func_0209bd04(r4) == 0) {
                if (func_0209bba0(r4) == 3) {
                    if (func_0209bc40(r4) == 4) {
                        func_0207dcf4(p);
                    }
                    func_0209baf4(r7);
                    func_0209c270((unsigned char *) func_0209b5ec(r6));
                }
            }
        }
    }
}
