/* villager_talk_greeting: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202c424 @ 0x0202c424, 0x158 bytes, Thumb
 * func_0202c420 @ 0x0202c420, 0x4 bytes, Thumb
 * func_0202c3f0 @ 0x0202c3f0, 0x30 bytes, Thumb
 * func_0202c3e4 @ 0x0202c3e4, 0xc bytes, Thumb
 * func_0202c388 @ 0x0202c388, 0x5c bytes, Thumb
 * func_0202c37c @ 0x0202c37c, 0xc bytes, Thumb
 * func_0202c350 @ 0x0202c350, 0x2c bytes, Thumb
 * func_0202c31c @ 0x0202c31c, 0x34 bytes, Thumb
 * func_0202c2c4 @ 0x0202c2c4, 0x58 bytes, Thumb
 * func_0202c2a8 @ 0x0202c2a8, 0x1c bytes, Thumb
 * func_0202c27c @ 0x0202c27c, 0x2a bytes, Thumb
 * func_0202c254 @ 0x0202c254, 0x28 bytes, Thumb
 * func_0202c248 @ 0x0202c248, 0xc bytes, Thumb
 * func_0202c23c @ 0x0202c23c, 0xc bytes, Thumb
 * func_0202c230 @ 0x0202c230, 0xc bytes, Thumb
 * func_0202bdb4 @ 0x0202bdb4, 0x47c bytes, Thumb
 * func_0202bd7c @ 0x0202bd7c, 0x38 bytes, Thumb
 * func_0202bd40 @ 0x0202bd40, 0x3c bytes, Thumb
 * func_0202bcd4 @ 0x0202bcd4, 0x6c bytes, Thumb
 * func_0202bca0 @ 0x0202bca0, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct Node Node;

struct NodeVT {
    void *pad_00[25];
    void *(*unk_64)(Node *);
};

struct Node {
    struct NodeVT *vt;
};

typedef struct {
    char pad_00[0x100];
    Node *unk_100;
    char pad_104[0x28];
    void *unk_12C;
} UnkStruct_0202c424;

typedef struct {
    int a, b;
} St;

typedef struct {
    char pad_00[0x1d];
    unsigned char b0 : 2;
    unsigned char b2 : 1;
} UnkStruct_0202c424_2;

struct UnkStruct_0202c350 {
    char pad_00[0x12c];
    int unk_12C;
};

struct Spad {
    char pad_00[0x1d];
    unsigned char b : 1;
};

struct UnkStruct_0202c254 {
    char pad_00[0x1d];
    unsigned char flag : 1;
};

typedef struct {
    int a;
    int b;
    int pad[3];
} UnkStruct_0202bdb4;

typedef struct {
    u8 pad[0x830];
    void *unk_830;
} UnkStruct_0202bdb4_2;

typedef struct {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad_44[0x100 - 0x44];
    UnkStruct_0202bdb4_2 *unk_100;
    char unk_104[0x1e];
    u8 unk_122;
    u8 pad_123[0x12c - 0x123];
    int unk_12C;
    u8 pad_130[0x13c - 0x130];
    u8 unk_13C;
    u8 pad_13D[0x19c - 0x13d];
    u16 unk_19C;
    u8 unk_19E;
} UnkStruct_0202bdb4_3;

typedef struct {
    void *p;
    u8 b;
} UnkStruct_0202bdb4_4;

typedef struct {
    int a;
    u8 b;
} ErrData;

typedef struct {
    u8 pad[0x1d];
    u8 unk_1D;
} UnkStruct_0202bdb4_5;

typedef struct UnkStruct_0202bcd4 UnkStruct_0202bcd4;

typedef struct UnkStruct_0202bcd4_2 {
    char pad_00[0x100];
    UnkStruct_0202bcd4 *unk_100;
} UnkStruct_0202bcd4_2;

struct UnkStruct_0202bcd4 {
    char pad_00[0x830];
    void *unk_830;
};

typedef struct B_s {
    char pad_00[0x830];
    int unk_830;
} B_s;

typedef struct A_s {
    char pad_00[0x100];
    B_s *unk_100;
    char pad_after[0x24];
    int unk_128;
    int unk_12C;
} A_s;

extern void *func_02099870(void *);
extern int func_020951bc(void *);
extern int func_02094ffc(void *);
extern unsigned short *func_02095040(void *);
extern void *func_02081d60(void *);
extern unsigned short *func_02081d64(void *);
extern void *func_02081e10(void *);
extern int memcmp(const void *, const void *, unsigned int);
extern void func_0209e474(St *);
extern int func_0209e3ac(void *, St *, int);
extern int func_0209e380(void *, St *);
extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern UnkStruct_0202c424_2 *func_0207f270(void *);
extern unsigned short data_021dc7aa[7];
extern unsigned char data_020e54a8;
extern int func_ov003_0222d77c(void);
extern int func_020984e8(void);
extern int func_0207ef48(int);
extern int func_020800fc(int);
extern int func_02015e70(int, int, int);
extern int func_0209dcac(void);
extern unsigned char data_020c8f64[];
extern int data_020c8cf8;
extern int func_0202c934(void *out, const void *src, int mode, int param, int size);
extern unsigned char data_020c892c[];
extern int data_020c8b40;
extern int func_020644cc(int);
extern void func_02015de4(void *self, unsigned short *p, int a, int b);
extern int func_0209975c(int);
extern unsigned char data_020c89f0[];
extern ErrData data_020c89f8;
extern ErrData data_020c8b28;
extern ErrData data_020c8dd8;
extern ErrData data_020c8ca0;
extern ErrData data_020c8d10;
extern ErrData data_020c89d0;
extern ErrData data_020c8a38;
extern ErrData data_020c8970;
extern ErrData data_020c8c88;
extern ErrData data_020c8ac8;
extern ErrData data_020c8c70;
extern ErrData data_020c8c38;
extern ErrData data_020c8c90;
extern ErrData data_020c8a80;
extern ErrData data_020c8a78;
extern ErrData data_020c8cf0;
extern ErrData data_020c8a18;
extern ErrData data_020c8b78;
extern ErrData data_020c8a00;
extern ErrData data_020c8b90;
extern ErrData data_020c8b60;
extern ErrData data_020c8bc8;
extern ErrData data_020c8d80;
extern ErrData data_020c8c58;
extern void *data_020ccf94;
extern int func_020036e8(int a);
extern void *func_020794c4(UnkStruct_0202bdb4_5 *a);
extern int func_020ba4e4(void);
extern int func_0207dd1c(void *a);
extern int func_020ae32c(void);
extern int func_020ae2c4(void);
extern void *func_020ae774(void *a);
extern int func_020ae3b8(unsigned int a);
extern int func_020ae5bc(int a, void *b);
extern void func_02068404(int a, int b, void *c);
extern void *func_020ae75c(void *a);
extern int func_02073d90(void *a);
extern int func_02081864(void *record);
extern int func_02099fe8(void);
extern void func_02063ccc(UnkStruct_0202bdb4 *o, int a, int b);
extern void func_020638d4(u16 *out, UnkStruct_0202bdb4 *o, int a, int b, int c, int d, int e);
extern void func_02063cc8(UnkStruct_0202bdb4 *o);
extern void func_02081878(int a);
extern int func_020b6730(void);
extern void *func_0207f1c8(void *a);
extern void *func_0209b5ec(void *);
extern int func_0209c330(void *a);
extern int func_020b65c4(void);
extern int func_020b66d8(void);
extern int func_020b671c(int a);
extern int func_020b6680(void);
extern void *func_0207944c(UnkStruct_0202bdb4_5 *a);
extern int func_020793c4(void *a);
extern int func_0202da38(UnkStruct_0202bdb4_3 *self, char *name, u8 *b, int len, int c, int d, int e, int f, int g);
extern void func_02015fb0(UnkStruct_0202bdb4_3 *self, int a, int b, int c, int d, int e);
extern unsigned char data_021f3b30[];
extern int func_0209c54c(int *, int);
extern int func_02015dd4(void *, int, char *, int, char *);
extern unsigned char *func_020808b0(unsigned char *arg);
extern unsigned char data_020d9fb4[];
extern int func_02080a2c(void *ptr);
extern char func_02082264(unsigned char *);
extern int data_020d9f48;
extern unsigned char data_020c8938[];
extern void func_0202d8f8(A_s *a, int *b, int *c, int d, int e);

void func_0202bcd4(UnkStruct_0202bcd4_2 *self);

int func_0202c424(UnkStruct_0202c424 *s, int *out)
{
    unsigned long long self = (unsigned long) s;
    unsigned long long output = (unsigned long) out;
    St st;
    void *h;
    void *a;
    unsigned short *p;
    unsigned short *identity;
    unsigned short *q;
    unsigned short *g;
    void *n;
    int flag;

    if ((void *) func_020984e8() != 0) {
        a = func_02099870((void *) func_020984e8());
    } else {
        a = 0;
    }
    st.a = 0;
    identity = data_021dc7aa;
    st.b = 0;
    if (((UnkStruct_0202c424 *) (unsigned long) self)->unk_12C == 0) {
        return 0;
    }
    if (a != 0 && func_020951bc(a) != 0 && func_02094ffc(a) != 0) {
        p = func_02095040(a);
        q = func_02095040(func_02081d60(((UnkStruct_0202c424 *) (unsigned long) self)->unk_12C));
        if (q[0] != p[0] || memcmp((char *) q + 2, (char *) p + 2, 0xc) != 0) {
            return 6;
        }
    }
    func_0209e474(&st);
    h = func_02081e10(((UnkStruct_0202c424 *) (unsigned long) self)->unk_12C);
    g = (unsigned short *) (char *) &data_021dc7aa[0];
    if (g != 0) {
        q = func_02081d64(((UnkStruct_0202c424 *) (unsigned long) self)->unk_12C);
        if (data_021dc7aa[0] != q[0] || memcmp((char *) identity + 2, (char *) q + 2, 0xc) != 0) {
            return 5;
        }
    }
    if (func_0209e3ac(h, &st, 0x3f) == 1) {
        return 1;
    }
    n = ((UnkStruct_0202c424 *) (unsigned long) self)
            ->unk_100->vt->unk_64(((UnkStruct_0202c424 *) (unsigned long) self)->unk_100);
    flag = 0;
    if (n != 0 && func_02003704(func_0208150c(n)) != 0 && func_0207f270(n) != 0) {
        if (func_0207f270(n)->b2 != 0) {
            flag = 1;
        }
    }
    *(int *) (unsigned long) output = func_0209e380(h, &st);
    if (func_02094ffc(a) != 0) {
        if (*(int *) (unsigned long) output >= 1 && flag == 0) {
            return 1;
        }
        return 2;
    }
    if (*(int *) (unsigned long) output >= 0x1e) {
        return 4;
    }
    if (*(int *) (unsigned long) output >= 7) {
        return 3;
    }
    if (*(int *) (unsigned long) output >= 1 && flag == 0) {
        return 1;
    }
    return 2;
}

int func_0202c420(void *self)
{
    return 0;
}

int func_0202c3f0(void *self)
{
    unsigned int ok;
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok > 0 && func_ov003_0222d77c() != 0) {
        return 1;
    }
    return 0;
}

int func_0202c3e4(int a, int b)
{
    if (b == 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0202c388(int a, int *b, int c)
{
    int r4;
    int r5 = 0;
    int r6 = 0;
    int r7 = 0;
    int sp0;

    r7 = a;
    r5 = (int) b;
    r6 = c;
    sp0 = func_020984e8();
    r4 = func_0207ef48(r6);
    if (r4 == 1) {
        if (func_02094ffc((void *) (int) func_02099870((void *) sp0)) != 0) {
            r4 = 0;
        }
    }
    if (r4 == 2) {
        func_02015e70(r7, func_020800fc(r6), 1);
    } else {
        *b = func_0209dcac();
    }
    return (int) &data_020c8f64[r4 * 8];
}

int func_0202c37c(int r0, int r1)
{
    if (r1 == 5) {
        return 1;
    } else {
        return 0;
    }
}

int *func_0202c350(struct UnkStruct_0202c350 *obj)
{
    if (obj->unk_12C) {
        func_02015e70((int) obj, (int) func_02081d64((void *) obj->unk_12C), 1);
    }
    return &data_020c8cf8;
}

int func_0202c31c(int unused, int *out, int param)
{
    int buffer[3];
    *out = func_0202c934(buffer, (const void *) data_020c892c, 2, param, 0x6000);
    return *out != -1;
}

void *func_0202c2c4(void *self, int param)
{
    int idx;
    unsigned short val;

    idx = param;
    if (param == -1) {
        idx = ((signed char *) data_020c892c)[func_020644cc(2)];
    }
    if (idx == -1) {
        goto done;
    }
    val = ((unsigned int) idx < 0x38) ? (unsigned short) (idx + 0x12b0) : 0x12b0;
    func_02015de4(self, &val, 0, 7);
done:
    return &data_020c8b40;
}

int func_0202c2a8(void *self)
{
    void *p;
    void *base;
    int (*fp)(void *);

    p = *(void **) ((char *) self + 0x100);
    base = *(void **) p;
    fp = *(int (**)(void *))((char *) base + 0xb0);
    return fp(p);
}

int func_0202c27c(int a, struct Spad *p)
{
    int res;
    unsigned bit;
    res = func_020984e8();
    bit = p->b;
    if (bit != 0) {
        goto fail;
    }
    if (res == 0) {
        goto fail;
    }
    if (func_0209975c(res) == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

void *func_0202c254(int a, int *b, struct UnkStruct_0202c254 *c)
{
    *b = func_0209dcac();
    c->flag = 1;
    return (void *) data_020c89f0;
}

int func_0202c248(int r0, int r1)
{
    if (r1 == 2) {
        return 1;
    }
    return 0;
}

int func_0202c23c(int r0, int r1)
{
    if (r1 == 3) {
        return 1;
    }
    return 0;
}

int func_0202c230(int param1, int param2)
{
    if (param2 == 4) {
        return 1;
    } else {
        return 0;
    }
}

void func_0202bdb4(UnkStruct_0202bdb4_3 *self, UnkStruct_0202bdb4_4 *out)
{
    void *local18;
    UnkStruct_0202bdb4_5 *obj;
    int local20;
    void *local24;
    int local28;
    u16 h[2];
    int num;
    int code2;
    int val;
    UnkStruct_0202bdb4 o;
    char b0[0x34];
    ErrData *err;
    int mode;
    int r6;
    int code;
    int n;

    local18 = self->unk_100->unk_830;
    obj = (UnkStruct_0202bdb4_5 *) func_0207f270(local18);
    local20 = func_020036e8((int) func_0208150c(local18));
    num = 0;
    r6 = func_0202c424((UnkStruct_0202c424 *) self, &num);
    local24 = func_020794c4(obj);
    mode = func_020ba4e4();
    code2 = 0;
    func_020984e8();
    local28 = 0;
    code = -1;
    h[0] = 0xfff1;
    val = -1;
    func_0202bcd4((UnkStruct_0202bcd4_2 *) self);

    if (func_0202c420((void *) self) != 0) {
        err = &data_020c89f8;
        if (r6 == 0) {
            self->unk_13C = 1;
        }
    } else if (func_0202c3f0((void *) self) != 0) {
        err = &data_020c8b28;
        if (r6 == 0) {
            self->unk_13C = 1;
        }
    } else if (func_0202c3e4((int) self, r6) != 0) {
        err = (ErrData *) func_0202c388((int) self, &code2, (int) local18);
    } else if (r6 == 6) {
        err = &data_020c8dd8;
        code2 = 7;
        local28 = 3;
    } else if (func_0202c31c((int) self, &val, (int) ((char *) self->unk_100 + 0x5c)) != 0) {
        err = (ErrData *) func_0202c2c4((void *) self, val);
    } else if (func_0202c2a8((void *) self) != 0) {
        err = &data_020c8ca0;
    } else if (func_0202c37c((int) self, r6) != 0) {
        err = (ErrData *) func_0202c350((struct UnkStruct_0202c350 *) self);
    } else if (r6 == 4) {
        err = &data_020c8d10;
        if (num >= 0x186) {
            code = 1;
            code2 = 5;
            local28 = code;
        }
    } else if (r6 == 3) {
        err = &data_020c89d0;
    } else if (func_0202c27c((int) self, (struct Spad *) obj) != 0) {
        err = (ErrData *) func_0202c254((int) self, &code2, (struct UnkStruct_0202c254 *) obj);
    } else if (func_0202c248((int) self, (int) local24) != 0) {
        err = &data_020c8a38;
    } else if (func_0202c23c((int) self, (int) local24) != 0) {
        err = &data_020c8970;
    } else if (func_0202c230((int) self, (int) local24) != 0) {
        err = &data_020c8c88;
    } else if (func_0207dd1c(local18) != 0 && func_020ae32c() != 0 && func_020ae2c4() == 0) {
        func_020ae774(b0);
        func_020ae5bc(func_020ae3b8((unsigned int) data_021f3b30), b0);
        err = &data_020c8ac8;
        func_02068404(self->unk_40, 4, b0);
        func_020ae75c(b0);
    } else if (func_02073d90(data_020ccf94) == 0 && self->unk_12C != 0 && func_02081864((void *) self->unk_12C) != 0 &&
               func_02099fe8() != -1) {
        err = &data_020c8c70;
        func_02063ccc(&o, 0, 0);
        func_020638d4(&h[1], &o, 0, 0, 1, 1, 0);
        self->unk_19C = h[1];
        func_02063cc8(&o);
        self->unk_19E = 0;
        func_02015de4((void *) self, (unsigned short *) (&self->unk_19C), 0, 7);
        if (self->unk_12C != 0) {
            func_02081878(self->unk_12C);
        }
    } else if (func_020b6730() != 0) {
        err = &data_020c8c38;
        if (func_0209c330((func_0209b5ec((void *) func_0207f1c8(local18)))) != 4) {
            code2 = 1;
        }
    } else if (func_020b65c4() == 0xa) {
        err = &data_020c8c90;
        if (func_0209c330((func_0209b5ec((void *) func_0207f1c8(local18)))) != 3) {
            code2 = 1;
        }
    } else if (func_020b66d8() != 0 && func_020b671c(func_020b65c4()) == 1) {
        err = &data_020c8a80;
    } else if (r6 == 1) {
        if (func_020b6680() != 0) {
            err = &data_020c8a78;
        } else if (mode == 1) {
            err = &data_020c8cf0;
        } else if (mode == 2) {
            err = &data_020c8a18;
        } else {
            err = &data_020c8b78;
        }
        code2 = func_0209dcac();
    } else if (func_0209c330((func_0209b5ec((void *) func_0207f1c8(local18)))) == 8) {
        err = &data_020c8a00;
    } else if (func_020793c4(func_0207944c(obj)) != 0) {
        err = &data_020c8b90;
        if (func_020793c4(func_0207944c(obj)) == 2) {
            code2 = 1;
        }
    } else if (local24 == (void *) 1) {
        err = &data_020c8b60;
        code2 = func_0209dcac();
    } else {
        unsigned int ok;
        if ((*(u8 *) &data_020e54a8) == 0) {
            ok = 1;
        } else {
            ok = 0;
        }
        if (ok != 0 && mode == 1) {
            err = &data_020c8bc8;
        } else if (ok != 0 && mode == 2) {
            err = &data_020c8d80;
        } else {
            err = &data_020c8c58;
            if (func_020644cc(9) != 0) {
                local28 = (u8) (err->b - 1);
            }
            code2 = func_0209dcac();
        }
    }

    if (err != 0) {
        if (code == -1) {
            code = err->b;
        }
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, local20, err->a, (u8) code, code2, local28);
    }

    n = num;
    if (n > 0) {
        int t;
        if (n >= 0x46) {
            t = 9;
        } else {
            t = n / 7;
        }
        if (n >= 0x186) {
            n = 0xc;
        } else {
            n = n / 0x1e;
        }
        func_02015fb0(self, t, 2, 1, 0, 0);
        func_02015fb0(self, n, 3, 2, 0, 0);
    }
    obj->unk_1D |= 4;
    out->p = self->unk_104;
    out->b = self->unk_122;
}

int func_0202bd7c(void *p1, int p2, int p3)
{
    int local = 0;
    char buf[2];
    int retval;

    retval = func_0209c54c(&local, p3);
    buf[0] = (char) local;
    buf[1] = '\0';
    return func_02015dd4(p1, p2, buf, retval, &buf[1]);
}

void func_0202bd40(int arg0, int arg1, unsigned char *arg2)
{
    unsigned char *p = func_020808b0(arg2);
    if (p) {
        unsigned char buf[2];
        buf[0] = *p;
        buf[1] = 0;
        func_02015dd4((void *) arg0, arg1, (char *) buf, (int) data_020d9fb4, (char *) (&buf[1]));
    }
}

void func_0202bcd4(UnkStruct_0202bcd4_2 *self)
{
    void *ptr;
    char buf[2];
    int i;

    ptr = self->unk_100->unk_830;
    if (ptr != 0) {
        buf[0] = func_02082264((unsigned char *) func_02080a2c(ptr));
        buf[1] = 0;
        func_02015dd4(self, 0, buf, (int) (&data_020d9f48), buf + 1);
        func_0202bd40((int) self, 6, (unsigned char *) ptr);
    }
    for (i = 0; i < 4; i++) {
        func_0202bd7c(self, i + 7, (unsigned char) data_020c8938[i]);
    }
}

void func_0202bca0(A_s *a, void *event)
{
    func_0202d8f8(a, &a->unk_12C, &a->unk_128, a->unk_100->unk_830, 0);
}
