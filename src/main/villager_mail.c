/* villager_mail: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02081418 @ 0x02081418, 0xdc bytes, Thumb
 * func_02081398 @ 0x02081398, 0x80 bytes, Thumb
 * func_02081144 @ 0x02081144, 0x254 bytes, Thumb
 * func_02080ff8 @ 0x02080ff8, 0x14c bytes, Thumb
 * func_02080fc0 @ 0x02080fc0, 0x38 bytes, Thumb
 * func_02080ea4 @ 0x02080ea4, 0x11c bytes, Thumb
 * func_02080e5c @ 0x02080e5c, 0x48 bytes, Thumb
 * func_02080dc0 @ 0x02080dc0, 0x9c bytes, Thumb
 * func_02080d70 @ 0x02080d70, 0x50 bytes, Thumb
 * func_02080d0c @ 0x02080d0c, 0x64 bytes, Thumb
 * func_02080cf0 @ 0x02080cf0, 0x1a bytes, Thumb
 */

#include "types.h"

typedef struct {
    int b[8];
} UnkStruct_02081418;

struct LocalObj {
    unsigned short unk_00;
    unsigned char unk_02[12];
    unsigned char pad_0E[18]; // pad to 32 bytes total
};

// msg is eight bytes {b0, pad, h2, h4, h6}; ext[2] follows it at msg + 8.

typedef struct {
    u8 unk_00;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} Msg;

struct UnkStruct_02080ff8 {
    u16 unk_00;
    u16 unk_02;
    int unk_04;
    int unk_08;
};

struct UnkStruct_02080ff8_2 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_02080ea4 {
    int unk_00;
    int w1;
};

struct OBJ {
    int d[16];
};

typedef struct UnkStruct_02080dc0 {
    u8 pad_00[0x20];
} UnkStruct_02080dc0;

typedef struct UnkStruct_02080dc0_2 {
    u16 unk_00;
} UnkStruct_02080dc0_2;

typedef struct UnkStruct_021dc7a8 {
    u16 unk_00;
    UnkStruct_02080dc0_2 unk_02;
} UnkStruct_021dc7a8;

struct LocalObj_02080d0c {
    unsigned char pad_00[32];
};

extern char data_021dc7aa;
extern void *func_02065f7c(void *p);
extern void func_02081cc4(void *obj);
extern int func_02066830(void *a, void *p);
extern void func_020642d0(void *a, void *b);
extern int func_02065f18(void *p);
extern void func_02061b1c(u16 *dst, u16 *src, int one);
extern int func_0204bcdc(u16 *p);
extern void func_0207df18(void *self, u16 *p);
extern int func_020951bc(void *);
extern int func_0209527c(void *, void *);
extern int memcmp(const void *, const void *, unsigned int);
extern int func_0209518c(void *, void *);
extern int func_020807a8(void *, void *);
extern int func_02081cd8(void *object);
extern int func_0209526c(void *);
extern int func_0208150c(int);
extern int func_02099870(int);
extern int func_0206d7ac(int);
extern int func_0206d7a0(int);
extern void *func_02094fd4(void *);
extern void *func_02094fbc(void *);
extern int func_020644cc(int);
extern int func_0207d33c(int, int, int, int, void *);
extern signed char func_02081cec(int, int);
extern void *func_020a8228(void *);
extern void *func_020a8210(void *);
extern int func_0209c54c(void *, int);
extern void func_020a8c1c(void *);
extern void *func_020b49d4(void *, void *, int);
extern int func_0203d7c4(int, void *);
extern void *func_02095074(int, void *);
extern void func_02063ccc(void *, int, int);
extern void func_02063cc8(void *);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063414(void *, int, int, int, int, int, int, int, int, int);
extern int func_0207d3dc(void *, int, void *, void *, void *, u16 *);
extern int data_020cd43c[];
extern unsigned char data_020e199c[];
extern unsigned char data_020e1994[];
extern void *func_020984e8(void);
extern int func_02094ffc(void *a);
extern int func_02099020(void *a, int b);
extern u8 *func_020992e4(void *a);
extern void func_0209e474(void *a);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern int func_02081d20(void *a);
extern int func_02081910(void *a);
extern int func_0205a240(void *a, int b, void *c, int d, void *e, int f);
extern void func_02081938(void *a);
extern void *data_020cd448[];
extern int data_020e1988;
extern char data_021dc7bc[];
extern void *func_02098844(void *base, int index);
extern int func_02003704(void *);
extern int func_0203fc78(int, struct UnkStruct_02080ea4 *, int);
extern int func_020818d4(void *);
extern void *func_020b5630(struct OBJ *);
extern int func_020b45d0(struct OBJ *, int, int, int, int, int);
extern void func_020818fc(void *);
extern void *func_020b5618(struct OBJ *);
extern u8 data_020e197c[];
extern UnkStruct_021dc7a8 data_021dc7a8;
extern int data_020e1974;
extern void *func_020641c8(UnkStruct_02080dc0 *l);
extern int func_02064294(UnkStruct_02080dc0_2 *t);
extern void func_02064210(UnkStruct_02080dc0_2 *t, UnkStruct_02080dc0 *l);
extern void *func_020641b0(UnkStruct_02080dc0 *l);
extern int func_020807dc(void *, void *);
extern int func_020807c0(void *, int);

int func_02081418(void *self, void *p1)
{
    u16 w[2];
    UnkStruct_02081418 it;
    void *obj;
    int ret;
    void *x;
    int f;
    u16 a0, a1;

    obj = 0;
    x = func_02065f7c(p1);
    ret = 0;
    if (x != 0) {
        func_0209527c((void *) (&it), x);
        if (func_020951bc((void *) (&it)) != 0) {
            obj = (void *) func_020807a8(self, (void *) (&it));
        }
        func_0209526c((void *) (&it));
    }
    if (obj != 0) {
        func_02081cc4(obj);
        func_02066830((char *) self + 0x634, p1);
        func_020642d0((char *) self + 0x7dc, &data_021dc7aa);
        w[0] = (u16) func_02065f18(p1);
        if (w[0] != 0xfff1) {
            func_02061b1c(&w[1], &w[0], 1);
            if (func_0204bcdc(&w[1]) == 0) {
                f = 0;
                a0 = *(volatile u16 *) &w[1];
                a1 = *(volatile u16 *) &w[1];
                if (a1 >= 0x1100 && a0 <= 0x1143) {
                    f = 1;
                }
                if (f == 0 && !(a0 >= 0x1144 && a0 <= 0x1187)) {
                    goto done;
                }
            }
            func_0207df18(self, &w[0]);
        done:;
        }
        ret = 1;
    }
    return ret;
}

int func_02081398(void *arg0, struct LocalObj *arg1)
{
    int forwarded_value;

    void *p;
    struct LocalObj obj;

    p = func_02065f7c((char *) arg0 + 0x634);
    if (func_020951bc(arg1) == 0) {
        goto fail_early;
    }
    if (p == 0) {
        goto fail_early;
    }

    func_0209527c(&obj, p);

    if (arg1->unk_00 != obj.unk_00) {
        goto fail_cleanup;
    }
    if (memcmp(&arg1->unk_02, &obj.unk_02, 12) != 0) {
        goto fail_cleanup;
    }
    if (func_0209518c(arg1, &obj) == 0) {
        goto fail_cleanup;
    }
    if ((forwarded_value = (int) func_020807a8(arg0, arg1)) == 0) {
        goto fail_cleanup;
    }
    if (func_02081cd8((void *) forwarded_value) == 0) {
        goto fail_cleanup;
    }

    func_0209526c(&obj);
    return 1;

fail_cleanup:
    func_0209526c(&obj);
fail_early:
    return 0;
}

void func_02081144(int p0, int p1, int p2)
{
    int ctx;          // sp+18
    int state;        // sp+1c
    int selres;       // sp+20
    Msg msg;          // sp+24
    u16 ext[2];       // sp+2c
    int cnt;          // sp+30
    int t34[2];       // sp+34
    int t3c[2];       // sp+3c
    int t44[2];       // sp+44
    int t4c[2];       // sp+4c
    int t54[2];       // sp+54
    int t5c[2];       // sp+5c
    int buf64[8];     // sp+64
    char obj84[0x5c]; // sp+84
    int r4;
    int type;
    int r7;
    int i;
    int t;
    int rnd;

    ctx = func_0208150c(p0);
    if (p1 == 0) {
        return;
    }
    if (func_02099020((void *) p1, 1) != 0) {
        return;
    }
    if (func_02003704((void *) ctx) == 0) {
        return;
    }
    r7 = func_02099870(p1);
    if (func_020951bc((void *) r7) == 0) {
        return;
    }
    r4 = func_020807a8((void *) p0, (void *) r7);
    type = func_0206d7ac(p2);
    func_02094fd4(buf64);

    switch (type) {
        case 1: {
            rnd = func_020644cc(3);
            func_0207d33c((unsigned int) data_020e1994, rnd, r7, ctx, 0);
            if (r4 == 0) {
                goto tail;
            }
            func_02081cec(r4, ~2);
            goto tail;
        }
        case 2: {
            msg.unk_02 = 0xfff1;
            func_020a8228(obj84);
            state = 0;
            cnt = 0;
            func_02095074(r7, buf64);
            func_0203d7c4(0, buf64);
            for (i = 0; i < 6; i++) {
                selres = func_0209c54c(&cnt, i);
                func_020a8c1c(obj84);
                msg.unk_00 = (u8) cnt;
                func_020b49d4(obj84, &msg, selres);
                func_0203d7c4(i + 2, obj84);
            }
            if (func_02065f18((void *) p2) != 0xfff1) {
                t = func_0206d7a0(p2);
                if (t <= 0x20) {
                    if (func_020644cc(2) == 0) {
                        func_02063ccc(t34, 2, 0);
                        t4c[0] = t34[0];
                        t4c[1] = t34[1];
                        func_020638d4(&msg.unk_04, t4c, 0, 0, 1, 1, 0);
                        msg.unk_02 = msg.unk_04;
                        func_02063cc8(t4c);
                        func_02063cc8(t34);
                    } else {
                        func_02063414(&msg.unk_06, 0x1518, 5, 0, 0, 0, 1, 0xa, 0, 1);
                        msg.unk_02 = msg.unk_06;
                    }
                } else if (t <= 0x2f) {
                    func_02063ccc(t3c, 0, 0);
                    t54[0] = t3c[0];
                    t54[1] = t3c[1];
                    func_020638d4(&ext[0], t54, 0, 0, 1, 1, 0);
                    msg.unk_02 = ext[0];
                    func_02063cc8(t54);
                    func_02063cc8(t3c);
                } else {
                    rnd = func_020644cc(3);
                    func_02063ccc(t44, data_020cd43c[rnd], 0);
                    t5c[0] = t44[0];
                    t5c[1] = t44[1];
                    func_020638d4(&ext[1], t5c, 0, 0, 1, 1, 0);
                    msg.unk_02 = ext[1];
                    func_02063cc8(t5c);
                    func_02063cc8(t44);
                }
                if (msg.unk_02 != 0xfff1) {
                    state = 0xa;
                }
            }
            func_0207d3dc((void *) data_020e199c, state, (void *) 0xa, (void *) r7, (void *) ctx, &msg.unk_02);
            if (r4 != 0) {
                if (func_02065f18((void *) p2) != 0xfff1) {
                    func_02081cec(r4, 5);
                } else {
                    func_02081cec(r4, 3);
                }
            }
            func_020a8210(obj84);
            goto tail;
        }
    }
tail:
    func_02094fbc(buf64);
}

void func_02080ff8(void *a0, void *a1, void *a2)
{
    int v10;
    struct UnkStruct_02080ff8 s;
    struct UnkStruct_02080ff8_2 b[2];
    u8 *p;
    int flag;
    void *r7;
    void *r5;
    void *ptr;

    v10 = func_0208150c((int) a0);
    if (a1 == 0) {
        a1 = func_020984e8();
    }
    if (func_02003704((void *) v10) == 0) {
        return;
    }
    if (a1 == 0) {
        return;
    }
    r7 = (void *) func_02099870((int) a1);
    if (func_020951bc(r7) == 0) {
        return;
    }
    if (func_02094ffc(r7) != 0) {
        return;
    }
    if (func_02099020(a1, 1) != 0) {
        return;
    }

    s.unk_04 = 0;
    s.unk_08 = 0;
    p = func_020992e4(a1);
    flag = 0;
    if (a2 == 0) {
        func_0209e474(&s.unk_04);
    } else {
        MI_CpuCopy8(a2, &s.unk_04, 8);
    }

    if (p[1] == ((u8 *) &s)[8] && p[0] == ((u8 *) &s)[7] && ((u8 *) &s)[6] >= 6) {
        flag = 1;
    }
    if (flag == 0) {
        return;
    }

    r5 = (void *) func_020807a8(a0, r7);
    if (r5 == 0) {
        return;
    }
    if (func_02081d20(r5) < 0x40) {
        return;
    }
    if (func_02081910(r5) != 0) {
        return;
    }

    s.unk_00 = 0xfff1;
    ptr = 0;
    func_02063ccc((void *) (&b[0]), (int) (data_020cd448[func_020644cc(3)]), 0);
    b[1].unk_00 = b[0].unk_00;
    b[1].unk_04 = b[0].unk_04;
    func_020638d4((void *) (&s.unk_02), (void *) (&b[1]), 0, 0, 1, 1, 0);
    s.unk_00 = s.unk_02;
    func_02063cc8((void *) (&b[1]));
    if (s.unk_00 != 0xfff1) {
        ptr = &s;
    }
    if (func_0205a240(&data_020e1988, (u8) func_020644cc(3), r7, v10, ptr, -1) != 0) {
        func_02081938(r5);
    }
    func_02063cc8((void *) (&b[0]));
}

void func_02080fc0(int p0, int p1)
{
    void *g = data_021dc7bc;
    int i;
    if (g != 0) {
        for (i = 0; i < 4; i++) {
            void *r = func_02098844(g, i);
            if (r != 0) {
                func_02080ff8((void *) p0, r, (void *) p1);
            }
        }
    }
}

void func_02080ea4(void *a0, void *a1, void *a2)
{
    struct UnkStruct_02080ea4 s;
    struct UnkStruct_02080ea4 s2;
    struct OBJ obj;
    void *h;
    void *m;
    void *w;
    int ok;

    h = (void *) func_0208150c((unsigned int) a0);
    if (a1 == 0) {
        a1 = func_020984e8();
    }
    if (func_02003704(h) == 0) {
        return;
    }
    if (a1 == 0) {
        return;
    }
    m = (void *) func_02099870((int) a1);
    if (func_020951bc(m) == 0) {
        return;
    }
    if (func_02094ffc(m) != 0) {
        return;
    }
    if (func_02099020(a1, 1) != 0) {
        return;
    }
    ok = 0;
    s.unk_00 = 0;
    s.w1 = 0;
    if (a2 == 0) {
        func_0209e474((void *) (&s));
    } else {
        MI_CpuCopy8(a2, &s, 8);
    }
    MI_CpuCopy8(&s, &s2, 8);
    if (func_0203fc78(0x13, &s2, 0) ? 1 : 0) {
        if (((u8 *) &s)[2] >= 6) {
            ok = 1;
        }
    }
    if (ok == 0) {
        return;
    }
    w = (void *) func_020807a8(a0, m);
    if (w == 0) {
        return;
    }
    if (func_02081d20((void *) w) < 0x40) {
        return;
    }
    if (func_020818d4(w) != 0) {
        return;
    }
    func_020b5630(&obj);
    func_020b45d0(&obj, ((u8 *) &s)[5] + 0x7d0, 4, 0, 0, 0);
    func_0203d7c4(2, (void *) (&obj));
    if (func_0205a240(data_020e197c, (u8) func_020644cc(3), m, (int) h, 0, 2) != 0) {
        func_020818fc(w);
    }
    func_020b5618(&obj);
}

void func_02080e5c(int p1, int p2)
{
    if ((int) ((int *) data_021dc7bc)) {
        int i;
        for (i = 0; i < 4; i++) {
            int r = (int) func_02098844((void *) ((int) ((int *) data_021dc7bc)), i);
            if (r != 0) {
                if (func_020951bc((void *) func_02099870(r)) != 0) {
                    func_02080ea4((void *) p1, (void *) r, (void *) p2);
                }
            }
        }
    }
}

void func_02080dc0(void *a, void *b)
{
    UnkStruct_02080dc0 l;
    int r6;
    UnkStruct_02080dc0_2 *t;
    void *p;
    r6 = func_0208150c((unsigned int) a);
    if (func_02003704((void *) r6) == 0) {
        return;
    }
    if (b == 0) {
        return;
    }
    p = (void *) func_02099870((int) b);
    if (func_020951bc(p) == 0) {
        return;
    }
    if (func_02094ffc(p) != 0) {
        return;
    }
    if (func_020807a8(a, p) == 0) {
        return;
    }
    func_020641c8(&l);
    t = &data_021dc7a8.unk_02;
    if (t != 0 && func_02064294(t) != 0) {
        func_02064210(t, &l);
        func_0203d7c4(2, (void *) (&l));
    }
    func_0205a240(&data_020e1974, (u8) ((u8) func_020644cc(5)), p, r6, 0, -1);
    func_020641b0(&l);
}

void func_02080d70(void *param)
{
    int i;
    void *x;

    if (func_02003704((void *) (unsigned int) func_0208150c((int) param)) != 0) {
        if ((unsigned int) ((unsigned char *) data_021dc7bc) != 0) {
            for (i = 0; i < 4; i++) {
                x = func_02098844((void *) ((unsigned char *) data_021dc7bc), i);
                if (x != 0) {
                    if (func_020951bc((void *) func_02099870((int) x)) != 0) {
                        func_02080dc0(param, x);
                    }
                }
            }
        }
    }
}

int func_02080d0c(void *arg0)
{
    int forwarded_value;

    int r;
    void *p;
    struct LocalObj_02080d0c obj;

    p = func_02065f7c((char *) arg0 + 0x634);
    if (p == 0) {
        goto fail_early;
    }
    func_0209527c(&obj, p);
    if (func_020951bc(&obj) == 0) {
        goto fail_cleanup;
    }
    r = func_020807dc(arg0, &obj);
    if ((forwarded_value = (int) func_020807c0(arg0, r)) == 0) {
        goto fail_cleanup;
    }
    if (func_02081cd8((void *) forwarded_value) == 0) {
        goto fail_cleanup;
    }
    func_0209526c(&obj);
    return r;
fail_cleanup:
    func_0209526c(&obj);
fail_early:
    return -1;
}

int func_02080cf0(void *argument0)
{
    int r0;
    int r2;
    int r1;

    r0 = func_02080d0c((void *) argument0);
    r2 = 0;
    r1 = ~r2;
    if (r0 != r1) {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}
