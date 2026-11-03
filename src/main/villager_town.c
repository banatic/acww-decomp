/* villager_town: 28 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207af90 @ 0x0207af90, 0xcc bytes, Thumb
 * func_0207af30 @ 0x0207af30, 0x60 bytes, Thumb
 * func_0207aeac @ 0x0207aeac, 0x84 bytes, Thumb
 * func_0207ae74 @ 0x0207ae74, 0x38 bytes, Thumb
 * func_0207ae34 @ 0x0207ae34, 0x40 bytes, Thumb
 * func_0207adf4 @ 0x0207adf4, 0x40 bytes, Thumb
 * func_0207acf8 @ 0x0207acf8, 0xfc bytes, Thumb
 * func_0207acbc @ 0x0207acbc, 0x3c bytes, Thumb
 * func_0207ac40 @ 0x0207ac40, 0x7a bytes, Thumb
 * func_0207ac20 @ 0x0207ac20, 0x1e bytes, Thumb
 * func_0207abd4 @ 0x0207abd4, 0x4c bytes, Thumb
 * func_0207ab0c @ 0x0207ab0c, 0xc8 bytes, Thumb
 * func_0207aa8c @ 0x0207aa8c, 0x80 bytes, Thumb
 * func_0207aa08 @ 0x0207aa08, 0x84 bytes, Thumb
 * func_0207a964 @ 0x0207a964, 0xa4 bytes, Thumb
 * func_0207a8ac @ 0x0207a8ac, 0xb8 bytes, Thumb
 * func_0207a810 @ 0x0207a810, 0x9c bytes, Thumb
 * func_0207a7f8 @ 0x0207a7f8, 0x16 bytes, Thumb
 * func_0207a764 @ 0x0207a764, 0x94 bytes, Thumb
 * func_0207a6a0 @ 0x0207a6a0, 0xc4 bytes, Thumb
 * func_0207a650 @ 0x0207a650, 0x50 bytes, Thumb
 * func_0207a62c @ 0x0207a62c, 0x24 bytes, Thumb
 * func_0207a5d0 @ 0x0207a5d0, 0x5c bytes, Thumb
 * func_0207a51c @ 0x0207a51c, 0xb4 bytes, Thumb
 * func_0207a500 @ 0x0207a500, 0x1c bytes, Thumb
 * func_0207a4c0 @ 0x0207a4c0, 0x40 bytes, Thumb
 * func_0207a47c @ 0x0207a47c, 0x44 bytes, Thumb
 * func_0207a44c @ 0x0207a44c, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x161];
    unsigned char unk_161;
} Res;

typedef struct Buf {
    int a;
    int b;
} Buf;

struct UnkStruct_0207ae34 {
    char pad_00[0x64];
    int unk_64;
};

typedef struct {
    char pad_00[0x64];
    int unk_64;
} GlobalType;

typedef struct {
    char data[0x7ec];
} Entry;

struct UnkStruct_0207acf8 {
    char pad_00[0x7ec];
};

struct UnkStruct_0207acbc {
    char pad_00[0x64];
    int unk_64;
};

typedef struct UnkStruct_0207ac40 {
    char pad_00[0x20];
    int unk_20;
    unsigned short unk_24;
} UnkStruct_0207ac40;

struct St {
    char data[20];
};

typedef struct {
    char data[0x7ec];
} UnkStruct_0207abd4;

typedef struct {
    unsigned short id;
    unsigned char pad_02[10];
} Entry_0207aa08;

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

typedef struct {
    unsigned char pad_00[0x7ec];
} UnkStruct_0207a8ac;

struct UnkStruct_0207a6a0_2 {
    u16 id;
};

typedef struct {
    unsigned short b[15];
} UnkStruct_0207a51c;

typedef struct {
    unsigned short unk_00;
    unsigned char m[12];
    unsigned char pad_0E;
    unsigned char unk_0F;
} Rec;

typedef struct UnkStruct_0207a47c {
    char pad_00[0x4078];
    unsigned short b0 : 1;
    unsigned short flag : 1;
    unsigned short val : 3;
} UnkStruct_0207a47c;

extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern int func_0207f270(char *p);
extern int func_020794d8(int x);
extern int func_0207cc54(int a, int b, int c);
extern int func_0207f150(char *p);
extern int func_0207b3dc(char *base);
extern Res *func_02079350(void);
extern void *data_020cd524[11];
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern int func_0203fc78(void *e, Buf *b, int k);
extern void *func_02041608(void);
extern void func_0209e29c(unsigned char *s, int v);
extern int func_0203fea0(unsigned char *p, unsigned char *buf);
extern void func_0207d2b4(unsigned char *, void *);
extern struct UnkStruct_0207ae34 *data_020ccf94;
extern void func_0207d128(void *);
extern int func_02073dd4(struct UnkStruct_0207ae34 *, int);
extern void func_0207d148(Entry *e);
extern int func_020951bc(int b);
extern struct UnkStruct_0207acf8 *func_0207cec0(struct UnkStruct_0207acf8 *a, struct UnkStruct_0207acf8 *res);
extern void func_02081888(unsigned short *);
extern int func_02073d90(struct UnkStruct_0207acbc *);
extern void func_0205ba64(void *p);
extern int func_0205b868(void *p, int q, unsigned short *r, int *s, int *t, int *u);
extern void func_0205ba60(void *p);
extern void func_020794c0(UnkStruct_0207abd4 *p, int x);
extern void func_020794a4(UnkStruct_0207abd4 *p, int x);
extern void func_0209e474(void *p);
extern void *func_02098844(int *g, int j);
extern int func_02099870(void *h);
extern int func_02099020(void *h, int n);
extern int func_02080998(char *p, int n, void *buf);
extern int func_02099174(void *h, int i);
extern int func_0205a1dc(int u, int t);
extern void func_02099164(void *h, int i, int v);
extern int func_02080928(void *p);
extern int func_02079924(void *p, int n, int i);
extern int func_020984e8(void);
extern int func_020791ec(void);
extern void func_02079204(char c);
extern void func_020791d4(char c);
extern int func_020791bc(void);
extern void func_0209a77c(void *p);
extern int func_02079544(int x);
extern void func_02079500(int x);
extern void func_02079540(int x, int y);
extern int func_020807a8(char *p, int x);
extern int func_02081898(int x);
extern void func_02079174(signed char);
extern int func_02081d20(int x);
extern void func_020791a4(char);
extern int func_020b65c4(void);
extern int func_02099734(void *);
extern int func_02098eb8(int);
extern struct UnkStruct_0207a6a0_2 *func_020992e4(void *);
extern int func_020992ac(void *);
extern void func_0207a180(void *);
extern int func_0209dd9c(void *a, void *b);
extern int func_0209dcdc(void *a, void *b);
extern char data_021dc7bc[];
extern void *func_02065f7c(void *p);
extern int func_0209527c(UnkStruct_0207a51c *it, void *x);
extern void *func_02098868(char *g, UnkStruct_0207a51c *it);
extern void *func_02065f64(void *p);
extern void *func_02099640(void *p);
extern int func_0209a9a8(void *a, void *b);
extern void *func_02003760(Rec *r, void *v);
extern void *func_0207ce98(void *self, Rec *r);
extern void func_02081144(void *a, void *b, void *c);
extern int func_02081418(void *a, void *b);
extern int func_02003750(Rec *r);
extern int func_0209526c(UnkStruct_0207a51c *it);
extern int func_0207cf14(void *, void *);
extern int func_0207cf74(int);
extern void func_0207d5bc(void *p);

void func_0207af90(char *base)
{
    int ret;
    int cnt;
    char *p;
    unsigned char mask;
    int i;
    int v;

    p = base;
    mask = 0;
    cnt = 0;
    ret = 0;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p))) {
            if (func_020794d8(func_0207f270(p)) == 0) {
                mask |= 1 << i;
                cnt++;
            }
        }
        p += 0x7ec;
    }
    v = func_0207cc54(mask, cnt, 8);
    if (v != -1) {
        ret = (unsigned char) v;
    } else {
        mask = 0;
        cnt = 0;
        p = base;
        for (i = 0; i < 8; i++) {
            if (func_02003704(func_0208150c(p))) {
                if (func_0207f150(p) == 3) {
                    if (i != func_0207b3dc(base)) {
                        mask |= 1 << i;
                        cnt++;
                    }
                }
            }
            p += 0x7ec;
        }
        v = func_0207cc54(mask, cnt, 8);
        if (v != -1) {
            ret = (unsigned char) v;
        }
    }
    func_02079350()->unk_161 = ret;
}

int func_0207af30(void)
{
    void **p;
    int i;
    int zero;
    unsigned int ok;
    void *e;
    unsigned int t;
    Buf b1;
    Buf b2;
    p = data_020cd524;
    b1.a = 0;
    b1.b = 0;
    func_0209e474((void *) (&b1));
    i = 0;
    zero = 0;
    ok = 0;
    for (; i < 11; p++, i++) {
        e = *p;
        MI_CpuCopy8(&b1, &b2, 8);
        if (func_0203fc78(e, &b2, zero) != 0) {
            t = 1;
        } else {
            t = ok;
        }
        if (t > 0) {
            if (e == func_02041608()) {
                return i;
            }
        }
    }
    return 11;
}

int func_0207aeac(unsigned int count, void *src)
{
    int out;
    int i;
    int j;
    int n;
    int k;
    unsigned char s[0x68];
    unsigned int *tbl;
    unsigned char *p;

    *(unsigned int *) &s[0] = 0;
    *(unsigned int *) &s[4] = 0;
    if (src == 0) {
        func_0209e474((void *) s);
    } else {
        MI_CpuCopy8(src, s, 8);
    }

    out = 0;
    j = 0;
    while (out <= count) {
        p = &s[0x10];
        MI_CpuCopy8(s, &s[8], 8);
        n = func_0203fea0(p, &s[8]);
        i = 0;
        while (i < n) {
            tbl = ((unsigned int *) data_020cd524);
            k = j;
            while (k < 0xb) {
                if (*(unsigned short *) p == *tbl) {
                    return k;
                }
                tbl++;
                k++;
            }
            p += 0xc;
            i++;
        }
        func_0209e29c(s, 1);
        out++;
    }
    return 0xb;
}

void func_0207ae74(unsigned char *arg0, void *arg1)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c((char *) arg0))) {
            func_0207d2b4(arg0, arg1);
        }
        arg0 += 0x7ec;
    }
}

void func_0207ae34(char *p)
{
    int i;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }

    for (i = 0; i < 8; i++) {
        if (func_02003704((int) ((void *) func_0208150c((char *) p))) != 0) {
            func_0207d128(p);
        }
        p += 0x7EC;
    }
}

void func_0207adf4(Entry *p)
{
    int i;

    if (func_02073dd4((struct UnkStruct_0207ae34 *) ((*(GlobalType * *) &data_020ccf94)), (*(GlobalType * *) &data_020ccf94)->unk_64) != 0) {
        return;
    }

    for (i = 0; i < 8; i++) {
        if (func_02003704((int) ((void *) (unsigned int) func_0208150c((char *) p))) != 0) {
            func_0207d148(p);
        }
        p++;
    }
}

void func_0207acf8(struct UnkStruct_0207acf8 *a, int b)
{
    unsigned short *condition_value0;
    u8 mask;
    int count;
    struct UnkStruct_0207acf8 *p;
    int i;
    struct UnkStruct_0207acf8 *res;

    if (func_020951bc(b) != 0) {
        p = a;
        mask = 0;
        count = 0;
        for (i = 0; i < 8; i++) {
            if (func_02003704(func_0208150c((char *) p)) != 0) {
                if (func_020794d8(func_0207f270((char *) p)) == 0) {
                    if (func_020807a8((char *) p, b) != 0) {
                        mask = (u8) (mask | (1 << i));
                        count++;
                    }
                }
            }
            p++;
        }
        res = (struct UnkStruct_0207acf8 *) func_0207cc54(mask, count, 8);
        if (func_0207cf74((unsigned int) res) == 0) {
            mask = 0;
            count = 0;
            p = a;
            for (i = 0; i < 8; i++) {
                if (func_02003704(func_0208150c((char *) p)) != 0) {
                    if (func_0207f150((char *) p) == 3) {
                        if (i != func_0207b3dc((char *) a)) {
                            if (func_020807a8((char *) p, b) != 0) {
                                mask = (u8) (mask | (1 << i));
                                count++;
                            }
                        }
                    }
                }
                p++;
            }
            res = (struct UnkStruct_0207acf8 *) func_0207cc54(mask, count, 8);
        }
        res = func_0207cec0(a, res);
        if (res != 0) {
            if (func_02003704(func_0208150c((char *) res)) != 0) {
                if ((condition_value0 = (unsigned short *) (func_020807a8((char *) res, b))) != 0) {
                    func_02081888(condition_value0);
                }
            }
        }
    }
}

void func_0207acbc(int a, int b)
{
    if (func_02073d90((*(struct UnkStruct_0207acbc * *) &data_020ccf94)) == 0) {
        func_0207acf8((struct UnkStruct_0207acf8 *) a, b);
    }
    if (func_02073dd4((struct UnkStruct_0207ae34 *) ((*(struct UnkStruct_0207acbc * *) &data_020ccf94)), (*(struct UnkStruct_0207acbc * *) &data_020ccf94)->unk_64) == 0) {
        func_0207ae34((char *) a);
    }
}

void func_0207ac40(int param1, int param2)
{
    unsigned short s;
    int a;
    int b;
    int c;
    struct St st;
    UnkStruct_0207ac40 *r5;

    r5 = (UnkStruct_0207ac40 *) func_0207cec0((struct UnkStruct_0207acf8 *) param1, (struct UnkStruct_0207acf8 *) param2);
    if (r5 == 0) {
        return;
    }

    if (func_02003704((int) ((void *) func_0208150c((char *) r5))) == 0) {
        return;
    }

    a = 5;
    b = 0;
    c = 0;
    s = 0;

    if (func_02003704((int) ((void *) func_0208150c((char *) r5))) == 0) {
        return;
    }

    r5 = (UnkStruct_0207ac40 *) func_0207f270((char *) r5);
    if (r5 == 0) {
        return;
    }

    func_0205ba64(&st);
    s = 0;

    r5->unk_20 = func_0205b868(&st, param2, &s, &a, &b, &c);
    r5->unk_24 = s;

    func_0205ba60(&st);
}

void func_0207ac20(void *param1)
{
    int i;
    void *p;

    p = param1;
    i = 0;
    do {
        func_0207ac40((int) p, i);
        i++;
    } while (i < 8);
}

void func_0207abd4(UnkStruct_0207abd4 *arr)
{
    int i;
    int a = 0;
    int b = 0;
    for (i = 0; i < 8; i++) {
        UnkStruct_0207abd4 *p = &arr[i];
        if (func_02003704(func_0208150c((char *) p))) {
            UnkStruct_0207abd4 *q;
            q = (UnkStruct_0207abd4 *) func_0207f270((char *) p);
            func_020794c0(q, a);
            q = (UnkStruct_0207abd4 *) func_0207f270((char *) p);
            func_020794a4(q, b);
        }
    }
}

void func_0207ab0c(char *p)
{
    // DECLS
    int t;
    int jstart;
    int u;
    int v;
    int z;
    int buf[2];
    int i;
    int j;
    void *h;
    int w;
    // ENDDECLS

    buf[0] = 0;
    buf[1] = 0;
    func_0209e474(buf);
    jstart = 0;
    z = 0;
    for (i = 0; i < 8; i++) {
        t = func_0208150c(p);
        if (func_02003704(t)) {
            if (func_0207f150(p) == 3) {
                for (j = jstart; j < 4; j++) {
                    h = func_02098844(((int *) data_021dc7bc), j);
                    if (h != 0) {
                        u = func_02099870(h);
                        if (func_020951bc(u)) {
                            if (func_02099020(h, 1) == 0) {
                                v = func_02080998(p, 7, buf);
                                if (v != ~z) {
                                    w = func_02099174(h, i);
                                    if (w != v) {
                                        if (func_0205a1dc(u, t)) {
                                            func_02099164(h, i, (unsigned char) v);
                                        }
                                    }
                                } else {
                                    func_02099164(h, i, 0xff);
                                }
                            }
                        }
                    }
                }
            }
        }
        p += 0x7ec;
    }
}

int func_0207aa8c(char *base, int n)
{
    char *p = base;
    int i;
    int best = 0xfffe7960;
    unsigned char mask = 0;
    int count = 0;
    for (i = 0; i < 8; p += 0x7ec, i++) {
        if (i == n) {
            continue;
        }
        if (!func_02080928(p)) {
            continue;
        }
        {
            int val = func_02079924(base + 0x3f60, n, i);
            if (val > best) {
                best = val;
                mask = (unsigned char) (1 << i);
                count = 1;
            } else if (val == best) {
                mask = (unsigned char) (mask | (1 << i));
                count++;
            }
        }
    }

    return func_0207cc54((unsigned char) mask, count, 8);
}

int func_0207aa08(const void *self, const void *param)
{
    int a;
    int i, count;
    Entry_0207aa08 *e;
    int k;
    unsigned char local8[8];
    Entry_0207aa08 entries[7];

    a = func_020984e8();
    if (a == 0) {
        goto fail;
    }
    if (func_02099020((void *) a, 1) != 0) {
        goto fail;
    }
    if (((const unsigned char *) param)[2] < 6) {
        goto fail;
    }

    MI_CpuCopy8(param, local8, 8);
    count = func_0203fea0((unsigned char *) entries, (unsigned char *) local8);

    for (i = 0; i < 8; self = (const char *) self + 0x7ec, i++) {
        if (func_02003704(func_0208150c((char *) self)) == 0) {
            continue;
        }
        if (func_0207f150((char *) self) != 3) {
            continue;
        }
        e = entries;
        k = 0;
        while (k < count) {
            if (e->id == i) {
                return i;
            }
            e++;
            k++;
        }
    }
fail:
    return -1;
}

void func_0207a964(void *obj)
{
    int forwarded_value;

    Pair p;
    int a;
    int b;

    p.unk_00 = 0;
    p.w1 = 0;
    b = func_020791ec();
    func_0209e474(&p);
    a = func_0207aa08((const void *) obj, (const void *) (&p));
    if (a == -1) {
        func_02079204(-1);
        func_020791d4(-1);
    } else if (a == b) {
        if ((forwarded_value = (int) (int) func_0207cec0((struct UnkStruct_0207acf8 *) obj, (struct UnkStruct_0207acf8 *) (func_020791bc()))) != 0) {
            if (func_02080928((void *) forwarded_value) != 0) {
                return;
            }
        }
        func_020791d4((char) func_0207aa8c((char *) obj, b));
    } else if (a != b) {
        b = func_0207aa8c((char *) obj, a);
        func_02079204((char) a);
        func_020791d4((char) b);
        if (a == func_0207b3dc((char *) obj)) {
            func_0209a77c((char *) obj + 0x3f90);
        }
    }
}

void func_0207a8ac(UnkStruct_0207a8ac *self)
{
    int id1;
    int id2;
    UnkStruct_0207a8ac *s;
    int i;
    void *p;

    id1 = func_020791ec();
    id2 = func_020791bc();
    s = self;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c((char *) s)) && func_02079544(func_0207f270((char *) s)) == 3) {
            func_02079500(func_0207f270((char *) s));
        }
        s++;
    }

    if (id1 != -1) {
        p = (void *) func_0207cec0((struct UnkStruct_0207acf8 *) self, (struct UnkStruct_0207acf8 *) id1);
        if (p != 0 && func_02003704(func_0208150c((char *) p))) {
            func_02079540(func_0207f270((char *) p), 0);
            p = (void *) func_0207cec0((struct UnkStruct_0207acf8 *) self, (struct UnkStruct_0207acf8 *) id2);
            if (p != 0 && func_02003704(func_0208150c((char *) p))) {
                func_02079540(func_0207f270((char *) p), 3);
            }
        } else {
            func_02079204(-1);
            func_020791d4(-1);
        }
    }
}

int func_0207a810(char *p)
{
    int ret;
    int v;
    unsigned char flags;
    int count;
    int i;

    ret = func_020984e8();
    if (ret != 0) {
        v = func_02099870((void *) ret);
    } else {
        v = 0;
    }

    if (v == 0) {
        goto fail;
    }
    if (func_020951bc(v) == 0) {
        goto fail;
    }

    flags = 0;
    count = 0;

    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p)) && func_020807a8(p, v) != 0 && func_02081898(func_020807a8(p, v)) == 0 &&
            func_020794d8(func_0207f270(p)) == 0) {
            flags |= (1 << i);
            count++;
        }
        p += 0x7ec;
    }

    return func_0207cc54(flags, count, 8);

fail:
    return -1;
}

void func_0207a7f8(char *argument0)
{
    func_02079174((signed char) func_0207a810((char *) argument0));
}

int func_0207a764(char *p, int v)
{
    int best;
    int count;
    int i;
    unsigned char flags;
    int t;
    int r;

    if (func_020951bc(v) == 0) {
        goto fail;
    }

    best = -128;
    flags = 0;
    count = 0;

    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p)) && func_0207f150(p) == 3) {
            t = func_020807a8(p, v);
            if (t != 0) {
                r = func_02081d20(t);
                if (r == best) {
                    flags |= (1 << i);
                    count++;
                } else if (r > best) {
                    best = r;
                    flags = (1 << i);
                    count = 1;
                }
            }
        }
        p += 0x7ec;
    }

    return func_0207cc54(flags, count, 8);

fail:
    return -1;
}

void func_0207a6a0(void *self, void *arg1)
{
    int p;
    struct UnkStruct_0207a6a0 {
        u32 a, b;
    } s;
    struct UnkStruct_0207a6a0_2 *r4;
    u8 b5;
    int cmp;

    if ((func_020791a4(-1), func_020b65c4()) != 6) {
        return;
    }

    if (arg1 == 0) {
        arg1 = (void *) func_020984e8();
    }
    if (arg1 == 0) {
        return;
    }

    if (func_02099020(arg1, 1) != 0) {
        return;
    }

    if (func_02098eb8(func_02099734(arg1)) == -1) {
        return;
    }

    p = func_02099870(arg1);
    r4 = func_020992e4(arg1);
    if (r4->id == 0) {
        return;
    }
    if (func_020951bc(p) == 0) {
        return;
    }

    s.a = 0;
    s.b = 0;
    func_0209e474(&s);

    b5 = ((u8 *) &s)[5];

    cmp = func_020992ac(arg1);
    if (cmp == b5) {
        return;
    }

    if (((u8 *) r4)[1] != ((u8 *) &s)[4]) {
        return;
    }
    if (((u8 *) r4)[0] != ((u8 *) &s)[3]) {
        return;
    }
    if (((u8 *) &s)[2] < 6) {
        return;
    }

    r4 = (struct UnkStruct_0207a6a0_2 *) func_0207a764((char *) self, p);
    if (func_0207cf74((int) r4) != 0) {
        func_0207a180((char *) self + 0x3f7c);
    }
    func_020791a4((signed char) (int) r4);
}

int func_0207a650(void *param0, void *param1)
{
    int ret = 1;
    unsigned char *base = (unsigned char *) param0;
    if (base[0x404F] != 0) {
        if (func_0209dd9c(param1, base + 0x404C) != 0) {
            if (func_0209dcdc(param1, base + 0x404C) < 14) {
                ret = 0;
            }
        } else {
            if (func_0209dcdc(base + 0x404C, param1) < 14) {
                ret = 0;
            }
        }
    }
    return ret;
}

void func_0207a62c(void *a, void *b)
{
    MI_CpuCopy8((const void *) b, (char *) a + 0x404c, 4);
    *((unsigned char *) a + 0x404f) = 1;
}

int func_0207a5d0(unsigned char *a, unsigned char *b)
{
    unsigned char *p;
    int i;

    if (func_020951bc((int) b) != 0) {
        p = (unsigned char *) func_0207cec0((struct UnkStruct_0207acf8 *) a, 0);
        for (i = 0; i < 8; i++) {
            if (func_02003704(func_0208150c((char *) p)) != 0) {
                if (func_020807a8((char *) p, (int) b) == 0) {
                    return 0;
                }
            }
            p += 0x7ec;
        }
        return 1;
    }
    return 0;
}

int func_0207a51c(void *self, void *p1)
{
    UnkStruct_0207a51c it;
    Rec rec;
    void *x;
    void *obj;
    void *y;
    int ret;

    if (p1 == 0) {
        goto fail;
    }
    x = func_02065f7c(p1);
    if (x == 0) {
        goto fail;
    }
    func_0209527c(&it, x);
    if (func_020951bc((int) (&it)) == 0) {
        goto cleanup_it;
    }
    obj = func_02098868(data_021dc7bc, &it);
    y = func_02065f64(p1);
    if (obj != 0) {
        func_0209a9a8(func_02099640(obj), p1);
    }
    if (y == 0) {
        goto cleanup_it;
    }
    func_02003760(&rec, y);
    if (func_02003704((int) (&rec)) == 0) {
        goto cleanup_rec;
    }
    y = func_0207ce98(self, &rec);
    if (y == 0) {
        goto cleanup_rec;
    }
    func_02081144(y, obj, p1);
    ret = func_02081418(y, p1);
    func_02003750(&rec);
    func_0209526c(&it);
    return ret;
cleanup_rec:
    func_02003750(&rec);
cleanup_it:
    func_0209526c(&it);
fail:
    return 0;
}

void func_0207a500(unsigned short *param)
{
    unsigned short *ptr;
    unsigned short val;

    ptr = (unsigned short *) ((unsigned int) param + 0x4078);
    val = *ptr;
    val &= ~2;
    *ptr = val;
    val = *ptr;
    val &= ~0x1c;
    *ptr = val;
}

void func_0207a4c0(void *arg0, void *argument1)
{
    int r4 = func_0207cf14(arg0, (void *) argument1);
    if (func_0207cf74(r4) != 0) {
        unsigned short *p = (unsigned short *) ((char *) arg0 + 0x4078);
        *p |= 2;
        *p = (*p & ~0x1c) | (((unsigned char) r4 & 7) << 2);
    }
}

int func_0207a47c(UnkStruct_0207a47c *s, int b)
{
    int v;

    if (s->flag != 0) {
        v = func_0207cf14(s, (void *) b);
        if (func_0207cf74(v) == 0) {
            goto ret0;
        }
        if (s->val != v) {
            goto ret0;
        }
        return 1;
    ret0:
        return 0;
    } else {
        return 0;
    }
}

void func_0207a44c(Entry *p)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c((char *) p))) {
            func_0207d5bc(p);
        }
        p++;
    }
}
