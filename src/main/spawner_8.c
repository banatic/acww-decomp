/* spawner_8: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02085d6c @ 0x02085d6c, 0xaa bytes, Thumb
 * func_02085d2c @ 0x02085d2c, 0x3e bytes, Thumb
 * func_02085c2c @ 0x02085c2c, 0x100 bytes, Thumb
 * func_02085be0 @ 0x02085be0, 0x4c bytes, Thumb
 * func_02085a30 @ 0x02085a30, 0x1b0 bytes, Thumb
 * func_020858ac @ 0x020858ac, 0x184 bytes, Thumb
 * func_020856fc @ 0x020856fc, 0x1b0 bytes, Thumb
 * func_02085558 @ 0x02085558, 0x1a4 bytes, Thumb
 * func_020854f4 @ 0x020854f4, 0x64 bytes, Thumb
 * func_0208541c @ 0x0208541c, 0xd8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x50];
    char grid[4];
} UnkStruct_02085d6c;

struct Pair {
    int a;
    int b;
};

typedef struct UnkStruct_02085c2c {
    u16 a;
    u16 b;
} UnkStruct_02085c2c;

typedef struct UnkStruct_02085a30_4 {
    u8 unk_00;
    u8 unk_01[2];
    u8 unk_03;
    u8 unk_04[5];
    u8 unk_09[0x15];
} UnkStruct_02085a30_4;

typedef struct UnkStruct_02085a30 {
    u8 unk_00;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} UnkStruct_02085a30;

typedef struct UnkStruct_02085a30_2 {
    int a, b;
} UnkStruct_02085a30_2;

typedef struct UnkStruct_02085a30_3 {
    UnkStruct_02085a30_2 p;
    int c;
} UnkStruct_02085a30_3;

typedef struct UnkStruct_020856fc_2 {
    u8 unk_00;
    u8 unk_01[3];
    u8 unk_04[5];
    u8 unk_09[0x15];
} UnkStruct_020856fc_2;

typedef struct UnkStruct_020856fc {
    int a, b;
} UnkStruct_020856fc;

typedef struct Gx {
    char pad_00[0x64];
    int unk_64;
} Gx;

typedef struct UnkStruct_02085558 {
    int a, b;
} UnkStruct_02085558;

typedef struct UnkStruct_02085558_2 {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_02085558_2;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_0208541c;

typedef struct {
    unsigned char pad_00[4];
} UnkStruct_0208541c_2;

extern int func_02084e90(void *);
extern int func_02084e40(void *, int, int);
extern int func_02084e20(void *, int, int);
extern int func_020644cc(int);
extern void func_0204f794(void *, int, int);
extern void func_0209e474(void *p);
extern int func_0203fc78(void *self, void *dst, int flag);
extern int func_0209fa30(void *x);
extern char data_021f3b85[];
extern int func_02084840(int x);
extern int func_020846cc(int x);
extern UnkStruct_02085c2c *func_020844c4(int x);
extern UnkStruct_02085c2c *func_02084388(int x);
extern UnkStruct_02085c2c *func_020842b8(int x);
extern UnkStruct_02085c2c *func_02084188(int x);
extern UnkStruct_02085c2c *func_02083fa4(void *a, void *b, int c, int d);
extern UnkStruct_02085c2c *func_02084058(int x);
extern u8 data_020d0684[];
extern u8 data_020d0654[];
extern int data_020d0648;
extern int func_02034270(void *obj, int a, int b, int c);
extern int func_0207f1d8(int a);
extern int func_020341c8(void *obj, int a);
extern unsigned char *func_020800d0(int a);
extern void func_0203423c(void *obj);
extern UnkStruct_02085a30_4 data_021d213c[];
extern int func_02082240(void);
extern void *func_0207cec0(int *, int);
extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern int func_0207c72c(int *, void *);
extern UnkStruct_02085a30_4 *func_020852e4(u16 *);
extern void func_02077a34(u8 *, UnkStruct_02085a30 *, int);
extern int func_020b65c4(void);
extern void func_02077978(u8 *, UnkStruct_02085a30_2 *, int *);
extern void MI_CpuCopy8(u8 *, u16 *, int);
extern int func_020a7278(void);
extern int func_020b6674(int);
extern int func_020b6654(int);
extern int func_02003348(int, int, UnkStruct_02085a30_2 *, u16 *, int);
extern int func_020b66b0(void);
extern int func_020791ec(void);
extern int func_020791bc(void);
extern int func_0207cf74(unsigned int);
extern int func_0207b3dc(void *g);
extern unsigned int func_0207b410(void *g);
extern int func_0209a654(unsigned char *);
extern int func_0207af30(void);
extern int func_0207f150(int st);
extern unsigned char data_021e5a2c[];
extern Gx *data_020ccf94;
extern int func_02073dd4(Gx *, int);
extern int func_020984e8(void);
extern void *func_02099640(int);
extern int func_0209bd44(char *);
extern int func_0209bc40(char *);
extern int func_0209e350(char *, UnkStruct_020856fc *);
extern unsigned int func_0209bba0(char *);
extern int func_0207cf14(int *, char *);
extern void func_020b23c8(void);
extern int func_0207ce98(int *, char *);
extern int func_0207f270(int object);
extern void func_02079500(unsigned char *);
extern unsigned char func_020b65b8(void);
extern void func_0207a7f8(int *);
extern int func_0207915c(void);
extern void *data_020d0644;
extern u8 data_020e54a8;
extern int data_020e1d8c;
extern void *func_0208602c(void);
extern void *func_020860c0(void *);
extern void *func_020860bc(void *);
extern void func_02087e00(void *);
extern void func_02087b10(void *);
extern void func_02087b04(void *);
extern int func_02087e38(void *);
extern void func_02087df4(void *);
extern int func_020b6660(void);
extern void func_0207a964(int *);
extern void func_0207a8ac(int *);
extern void func_02079174(int);
extern int func_0207aa08(int *, UnkStruct_02085558 *);
extern void func_02079204(int);
extern void func_020791d4(int);
extern int func_02084ad0(void);
extern void *func_02099870(void *);
extern void func_0207a340(int *, void *);
extern int func_020b6680(void);
extern int func_020b67d4(void);
extern int func_020b6804(void);
extern int func_02084c60(void *);
extern UnkStruct_02085558_2 *func_02084b74(void *, int *, void *);
extern void func_02084210(void *receiver);
extern void func_0207be8c(int *);
extern void func_02084b54(void *);
extern void func_02084dac(void *a);
extern void func_0207921c(void);
extern int func_020b5e70(void);
extern int func_020b6694(int);
extern int func_0207cd4c(void *a, signed char b);
extern void func_0207f454(int a);
extern u8 data_020e1ca8;
extern void func_020795f4(void);
extern void func_0207c6a4(UnkStruct_0208541c_2 *o);
extern int func_020825d8(unsigned short *w);
extern int func_020794c4(void *y);
extern void func_02079494(void *y);
extern int func_020794a0(void *y);
extern void func_020794c0(void *y, int z);
extern int func_0207944c(void *y);
extern void func_02079410(int a, int b);

int func_02085d6c(UnkStruct_02085d6c *o, void *p)
{
    int n, x, y, r, i, j;

    if (func_02084e90(&o->grid) != 0) {
        n = 0;
        for (x = 0; x < 0x10; x++) {
            func_02084e40(&o->grid, x, 0xe);
            func_02084e40(&o->grid, x, 0xf);
        }
        for (y = 0; y < 0xe; y++) {
            for (x = 0; x < 0x10; x++) {
                if (func_02084e20(&o->grid, x, y) != 0) {
                    n++;
                }
            }
        }
        if (n > 0) {
            r = func_020644cc(n);
            for (i = 0; i < 0xe; i++) {
                for (j = 0; j < 0x10; j++) {
                    if (func_02084e20(&o->grid, j, i) != 0) {
                        if (r == 0) {
                            func_0204f794(p, j, i);
                            return 1;
                        }
                        r--;
                    }
                }
            }
        }
    }
    return 0;
}

int func_02085d2c(void *self, const struct Pair *src)
{
    struct Pair local;
    struct Pair dst;
    local.a = 0;
    local.b = 0;
    if (src == 0) {
        func_0209e474(&local);
        src = &local;
    }
    MI_CpuCopy8((u8 *) src, (u16 *) (&dst), 8);
    if (func_0203fc78(self, &dst, 0) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02085c2c(u16 *p)
{
    int flag;
    int t;
    UnkStruct_02085c2c *q;

    flag = func_0209fa30(data_021f3b85);
    t = func_02084840(0);
    if (t == 0) {
        t = func_020846cc(0);
    }
    if (t) {
        *p = 0xfff1;
    } else if ((q = func_020844c4(0)) != 0) {
        *p = q->b;
    } else if ((q = func_02084388(0)) != 0) {
        *p = q->b;
    } else if (flag == 0 && func_02085d2c((void *) 0x3d, 0)) {
        *p = 0xd00e;
    } else if ((q = func_020842b8(0)) != 0) {
        *p = q->b;
    } else if ((q = func_02084188(0)) != 0) {
        *p = q->b;
    } else if ((q = func_02083fa4(data_020d0684, data_020d0654, data_020d0648, 0)) != 0) {
        *p = q->b;
    } else if (flag == 0 && func_02085d2c((void *) 0x3f, 0)) {
        *p = 0xd00a;
    } else if (flag == 0 && func_02085d2c((void *) 0x40, 0)) {
        *p = 0xd00b;
    } else if ((q = func_02084058(0)) != 0) {
        *p = q->b;
    } else {
        *p = 0xfff1;
    }
}

void func_02085be0(int param1, int param2)
{
    unsigned char obj[0x44];
    unsigned char *p;

    func_02034270(obj, param2, 0, 0);
    if (func_0207f1d8(param1) == 0 && func_020341c8(obj, 0) != 0) {
        p = func_020800d0(param1);
        func_0204f794((void *) param2, p[0] + 1, p[1] + 2);
    }
    func_0203423c(obj);
}

void func_02085a30(int p0)
{
    int lim;
    int cnt;
    int t;
    UnkStruct_02085a30 w;
    UnkStruct_02085a30_3 m;
    int i;
    void *e;
    UnkStruct_02085a30_4 *q;
    u8 *p;

    w.unk_02 = 0xfff1;
    w.unk_04 = 0;
    w.unk_06 = 0;
    w.unk_08 = 0;
    lim = func_02082240();
    cnt = 0;
    w.unk_00 = 0;
    if (lim <= 0) {
        return;
    }
    for (i = 0; i < 8 && cnt < lim; i++) {
        e = func_0207cec0(((int *) data_021e5a2c), i);
        if (e == 0) {
            continue;
        }
        if (func_02003704(func_0208150c(e)) == 0) {
            continue;
        }
        if (func_0207c72c(((int *) data_021e5a2c), func_0208150c(e)) == 0) {
            continue;
        }
        w.unk_00 = 0;
        m.p.a = 0;
        m.p.b = 0;
        m.c = 0;
        w.unk_04 = 0;
        w.unk_06 = 0;
        w.unk_08 = 0;
        w.unk_02 = (u16) ((i & 0xfff) | 0xe000);
        q = func_020852e4(&w.unk_02);
        if (q != 0 && q->unk_00 != 0) {
            func_02077a34(&q->unk_03, &w, 0);
            if (w.unk_00 == func_020b65c4()) {
                func_02077978(q->unk_04, &m.p, &m.c);
                MI_CpuCopy8(q->unk_09, &w.unk_06, 2);
            } else {
                p = (u8 *) func_020800d0((int) e);
                func_0204f794((void *) (&m.p), p[0] + 1, p[1] + 2);
            }
        } else if (func_020a7278() != 0 && data_021d213c[i].unk_00 != 0) {
            q = &data_021d213c[i];
            func_02077a34(&q->unk_03, &w, 0);
            t = w.unk_00;
            if (t != func_020b65c4() && func_020b6674(t) == 0 && func_020b6654(w.unk_00) == 0 && w.unk_00 != 0x2c) {
                p = (u8 *) func_020800d0((int) e);
                func_0204f794((void *) (&m.p), p[0] + 1, p[1] + 2);
            } else {
                func_02077978(q->unk_04, &m.p, &m.c);
                func_02085be0((int) e, (int) (&m.p));
            }
        } else {
            p = (u8 *) func_020800d0((int) e);
            func_0204f794((void *) (&m.p), p[0] + 1, p[1] + 2);
        }
        if (func_02003348(0x84, w.unk_02, &m.p, &w.unk_04, p0) != 0) {
            cnt++;
        }
    }
}

void func_020858ac(void *p)
{
    int key;
    int st;
    int res;
    int action;
    int flag;
    unsigned short cmd[5];
    int tmp[3];

    key = func_020b66b0();
    st = (int) func_0207cec0((int *) data_021e5a2c, key);
    if (st == 0) {
        goto exit;
    }

    if (!func_02003704((void *) (unsigned int) func_0208150c((void *) st))) {
        goto exit;
    }

    cmd[0] = 0xfff1;
    cmd[1] = 0xfff1;
    tmp[0] = 0;
    tmp[1] = 0;
    tmp[2] = 0;
    cmd[2] = 0;
    cmd[3] = 0;
    cmd[4] = 0;

    cmd[0] = (unsigned short) ((key & 0xfff) | 0xe000);

    res = (int) func_020852e4((u16 *) cmd);

    if (func_020a7278()) {
        res = func_02085d6c((UnkStruct_02085d6c *) p, tmp);
        cmd[3] = (unsigned short) (func_020644cc(4) << 14);
    } else if (res != 0 && *(unsigned char *) res != 0) {
        func_02077978((u8 *) ((void *) (res + 4)), (UnkStruct_02085a30_2 *) tmp, (int *) (&tmp[2]));
        res += 9;
        MI_CpuCopy8((u8 *) ((void *) res), (u16 *) (&cmd[3]), 2);
        res = 1;
    } else {
        res = func_02085d6c((UnkStruct_02085d6c *) p, tmp);
        cmd[3] = (unsigned short) (func_020644cc(4) << 14);
    }

    if (res == 0) {
        goto exit;
    }

    action = 0x85;
    flag = 0xd8;

    if (func_02073dd4((Gx *) ((*(void * *) &data_020ccf94)), *(int *) ((char *) (*(void * *) &data_020ccf94) + 0x64)) == 0) {
        if (key == func_020791ec()) {
            action = 0x80;
            if (func_0207cf74((unsigned int) func_020791bc()) != 0) {
                cmd[1] = (unsigned short) ((func_020791bc() & 0xfff) | 0xe000);
                flag = 0x81;
            }
        } else if (key == func_0207b3dc(data_021e5a2c)) {
            if (func_0209a654((unsigned char *) func_0207b410(data_021e5a2c)) == 0) {
                action = 0x83;
            }
        } else {
            if (func_0207af30() == 0xa && func_0207f150(st) == 3) {
                action = 0x86;
            }
        }
    }

    func_02003348(action, (unsigned short) cmd[0], (UnkStruct_02085a30_2 *) tmp, (u16 *) (&cmd[2]), (int) p);

    if (flag == 0xd8) {
        goto exit;
    }

    if (((cmd[1] & 0xf000) >> 12) == 0xe) {
        func_02085d6c((UnkStruct_02085d6c *) p, tmp);
        cmd[3] = (unsigned short) (func_020644cc(4) << 14);
        func_02003348(flag, (unsigned short) cmd[1], (UnkStruct_02085a30_2 *) tmp, (u16 *) (&cmd[2]), (int) p);
    }

exit:
    return;
}

void func_020856fc(int p0)
{
    int forwarded_value;

    u16 w[4];
    char *base;
    int idx;
    UnkStruct_020856fc v18;
    UnkStruct_020856fc_2 *e;
    int kind;
    UnkStruct_020856fc a20;
    char *obj;
    int r;
    int a28;
    int n;
    int z;
    int res;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }
    kind = 0x85;
    z = 0;
    a20.a = 0;
    a20.b = 0;
    a28 = 0;
    w[1] = 0;
    w[2] = 0;
    w[3] = 0;
    w[0] = 0xfff1;
    r = func_0207af30();
    if (r == 0xb) {
        base = (char *) func_02099640((int) func_020984e8()) + 0xa4;
        obj = base + 0x10;
        res = -1;
        if (func_0209bd44(obj) != 0 && func_0209bc40(obj) == 0x15) {
            v18.a = 0;
            v18.b = 0;
            func_0209e474((void *) (&v18));
            n = func_0209e350(base + 0x1c, &v18);
            if (func_0209bba0(obj) == 0) {
                if (n <= 0x1e) {
                    res = func_0207cf14(((int *) data_021e5a2c), base);
                }
            } else if (func_0209bba0(obj) < 4) {
                if (n <= 0x3c) {
                    res = func_0207cf14(((int *) data_021e5a2c), base);
                    if (func_0207cf74(res) != 0) {
                        e = &((UnkStruct_020856fc_2 *) data_021d213c)[res];
                        if (((UnkStruct_020856fc_2 *) data_021d213c)[res].unk_00 != 0) {
                            func_02077978(e->unk_04, (UnkStruct_02085a30_2 *) (&a20), &a28);
                            MI_CpuCopy8(e->unk_09, &w[2], 2);
                        }
                    }
                } else {
                    func_020b23c8();
                    if ((forwarded_value = (int) func_0207ce98(((int *) data_021e5a2c), base)) != 0) {
                        func_02079500((unsigned char *) func_0207f270((int) forwarded_value));
                    }
                }
            }
        }
        if (res != -1) {
            w[0] = (u16) ((res & 0xfff) | 0xe000);
            kind = 0x82;
            z = 1;
        }
    } else if (r == 0xa) {
        if (func_020b6674((int) func_020b65b8()) != 0) {
            func_0207a7f8(((int *) data_021e5a2c));
        }
        idx = func_0207915c();
        if (func_0207cf74(idx) != 0) {
            w[0] = (u16) ((idx & 0xfff) | 0xe000);
            kind = 0x87;
            if (func_020b6674((int) func_020b65b8()) == 0) {
                e = &((UnkStruct_020856fc_2 *) data_021d213c)[idx];
                if (((UnkStruct_020856fc_2 *) data_021d213c)[idx].unk_00 != 0) {
                    func_02077978(e->unk_04, (UnkStruct_02085a30_2 *) (&a20), &a28);
                    MI_CpuCopy8(e->unk_09, &w[2], 2);
                }
            }
            z = 1;
        }
    }
    if (z != 0) {
        func_02003348(kind, w[0], (UnkStruct_02085a30_2 *) (&a20), 0, p0);
    }
}

int func_02085558(void *self)
{
    UnkStruct_02085558 s;
    void *g6;
    int *w;
    int r;
    int x;
    void *y;
    UnkStruct_02085558_2 *q;
    unsigned int ok;

    g6 = data_020d0644;
    w = ((int *) data_021e5a2c);
    func_02087e00(func_020860c0(func_0208602c()));
    func_02087b10(func_020860bc(func_0208602c()));
    if (func_020b6660() != 0) {
        if ((int) w != 0) {
            func_0207a964(w);
            func_0207a8ac(w);
        }
        func_02079174(-1);
    } else {
        if (func_020b6674((int) (int) func_020b65b8()) != 0) {
            s.a = 0;
            s.b = 0;
            r = func_020791ec();
            func_0209e474((void *) (&s));
            if (r != -1) {
                if (r != func_0207aa08(w, &s)) {
                    func_02079204(-1);
                    func_020791d4(-1);
                    if ((int) w != 0) {
                        func_0207a8ac(w);
                    }
                }
            }
        }
    }
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok != 0) {
        if (func_02084ad0() == 0) {
            if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
                if ((void *) func_020984e8() != 0) {
                    y = func_02099870((void *) func_020984e8());
                } else {
                    y = 0;
                }
                func_0207a340(w, y);
            }
            func_02085a30((int) self);
        }
    } else if (func_020b6680() != 0) {
        func_020858ac(self);
    } else if (func_020b67d4() != 0) {
        if ((int) w != 0 && func_0207af30() != 0xa) {
            x = func_0207915c();
            if (x != -1) {
                func_02079174(-1);
                func_020b23c8();
            }
        }
        if (func_020b6804() == 0) {
            func_020856fc((int) self);
        }
    }
    func_02084c60(self);
    q = func_02084b74(self, &data_020e1d8c, g6);
    if (q != 0) {
        func_02087b04(func_020860bc(func_0208602c()));
        if (q->unk_02 == 0xd008) {
            if (func_02087e38(func_020860c0(func_0208602c())) == 0) {
                goto skip;
            }
        }
        func_02087df4(func_020860c0(func_0208602c()));
    }
skip:
    func_02084210(self);
    if (func_020b6660() != 0) {
        func_0207be8c(w);
    }
    return 1;
}

int func_020854f4(void *argument0)
{
    u8 *p;
    int v, w;
    func_02084b54((void *) argument0);
    func_02084dac(&data_020e1ca8);
    func_0207921c();
    if (func_020b6660()) {
        p = ((u8 *) data_021e5a2c);
        func_0207be8c((int *) p);
        v = func_020b5e70();
        if (func_020b6694(v)) {
            w = func_0207cd4c(p, (signed char) v);
            if (w) {
                if (func_02003704((void *) ((int) func_0208150c((void *) w)))) {
                    func_0207f454(w);
                }
            }
        }
    }
    return 1;
}

int func_0208541c(void)
{
    UnkStruct_0208541c_2 *o = ((UnkStruct_0208541c_2 *) data_021e5a2c);
    unsigned short w;
    void *x;
    void *y;
    int i;

    if (func_020b6660() != 0) {
        func_020795f4();
        if (func_02073dd4((Gx *) ((*(UnkStruct_0208541c * *) &data_020ccf94)), (*(UnkStruct_0208541c * *) &data_020ccf94)->unk_64) == 0 && o != 0) {
            func_0207c6a4(o);
        }
    }
    if (func_02073dd4((Gx *) ((*(UnkStruct_0208541c * *) &data_020ccf94)), (*(UnkStruct_0208541c * *) &data_020ccf94)->unk_64) == 0 && o != 0) {
        w = 0xfff1;
        for (i = 0; i < 8; i++) {
            x = func_0207cec0((int *) o, i);
            if (x != 0) {
                if (func_02003704((void *) ((int) func_0208150c(x))) != 0) {
                    y = (void *) func_0207f270((int) x);
                    if (y != 0) {
                        w = (unsigned short) ((i & 0xfff) | 0xe000);
                        if (func_020825d8(&w) == 0) {
                            if (func_020794c4(y) != 0) {
                                func_02079494(y);
                                if (func_020794a0(y) == 0) {
                                    func_020794c0(y, 0);
                                }
                                func_02079410(func_0207944c(y), 0);
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}
