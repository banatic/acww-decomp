/* fish_disp_3: 23 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205084c @ 0x0205084c, 0x38 bytes, Thumb
 * func_02050830 @ 0x02050830, 0x1a bytes, Thumb
 * func_02050814 @ 0x02050814, 0x1a bytes, Thumb
 * func_020507b8 @ 0x020507b8, 0x5c bytes, Thumb
 * func_0205072c @ 0x0205072c, 0x8c bytes, Thumb
 * func_02050704 @ 0x02050704, 0x28 bytes, Thumb
 * func_020506c0 @ 0x020506c0, 0x44 bytes, Thumb
 * func_0205066c @ 0x0205066c, 0x54 bytes, Thumb
 * func_020505f4 @ 0x020505f4, 0x78 bytes, Thumb
 * func_02050588 @ 0x02050588, 0x6c bytes, Thumb
 * func_02050444 @ 0x02050444, 0x144 bytes, Thumb
 * func_02050394 @ 0x02050394, 0xb0 bytes, Thumb
 * func_0205027c @ 0x0205027c, 0x118 bytes, Thumb
 * func_02050210 @ 0x02050210, 0x6c bytes, Thumb
 * func_02050140 @ 0x02050140, 0xd0 bytes, Thumb
 * func_020500d8 @ 0x020500d8, 0x68 bytes, Thumb
 * func_0205009c @ 0x0205009c, 0x3c bytes, Thumb
 * func_0205007c @ 0x0205007c, 0x20 bytes, Thumb
 * func_0204ff00 @ 0x0204ff00, 0x17c bytes, Thumb
 * func_0204fee8 @ 0x0204fee8, 0x18 bytes, Thumb
 * func_0204fed0 @ 0x0204fed0, 0x18 bytes, Thumb
 * func_0204feac @ 0x0204feac, 0x24 bytes, Thumb
 * func_0204fea4 @ 0x0204fea4, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x4c];
    unsigned int unk_50;
    unsigned char pad_54[0x5ac];
    unsigned int unk_600;
} UnkStruct_020507b8;

struct UnkStruct_02050704 {
    unsigned char pad_00[0x48];
    unsigned char unk_48[4];
    unsigned char unk_4C[4];
    unsigned char pad_50[0x48];
    unsigned char unk_98[4];
};

typedef struct Elem {
    unsigned char pad_00[0x44];
    int unk_44;
} Elem;

typedef struct {
    char pad_00[0x44];
    int unk_44;
    char pad_48[8];
} Elem_0205066c;

typedef struct UnkStruct_020505f4 {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    char pad_50[0x98 - 0x50];
    char unk_98[0x16c - 0x98];
} UnkStruct_020505f4;

struct Param {
    int unk_00;
    int unk_04;
    int state;
};

typedef struct Entry Entry;

struct Entry {
    u8 pad_00[0x40];
    int unk_40;
    u32 unk_44;
    u8 pad_48[0x44];
    int unk_8C[3];
    u8 unk_98[0x9c];
    u8 unk_134[0x30];
    int unk_164;
    u8 pad_168;
    u8 unk_169;
    u8 pad_16A[3];
};

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int w[12];
} Mtx;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x8c - 0x44];
    Vec3 unk_8C;
    char pad_98[0x15c - 0x98];
    short unk_15C, unk_15E, unk_160;
} UnkStruct_02050394_2;

typedef struct {
    char pad_00[8];
    int unk_08;
} UnkStruct_02050394;

typedef struct {
    u8 unk_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    u8 unk_50[0x98 - 0x50];
    int unk_98;
    u8 unk_9C[0x168 - 0x9c];
    u8 unk_168;
} UnkStruct_0205027c;

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    unsigned char unk_4C[0x98 - 0x4c];
    unsigned char unk_98[0x164 - 0x98];
    int unk_164;
} UnkStruct_02050140;

typedef struct {
    char pad_00[0x44];
    int type; // 0x44
    char pad_48[0x98 - 0x48];
    char data[0x150 - 0x98]; // 0x98
    int val0;                // 0x150
    int val1;                // 0x154
    int val2;                // 0x158
    char pad_15C[0x16c - 0x158 - 4];
} Entry_020500d8;

typedef struct {
    char pad_00[0x150];
    unsigned int unk_150;
    unsigned int unk_154;
    unsigned int unk_158;
} Dest;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Src;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char pad_02[2];
    int unk_04;
    int unk_08;
} UnkStruct_0204ff00;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0204feac;

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void func_02077978(const void *src, int *out1, int *out2);
extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *p);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_0209d2b8(void *arg);
extern unsigned char data_020da13c[];
extern unsigned char data_020dce48[];
extern void func_020f5958(char *);
extern void func_0209d34c(char *);
extern void *func_0209d11c(char *);
extern void *func_02055210(char *);
extern void func_0209d0a4(char *);
extern void *func_020551e0(void *ptr);
extern int func_0209d104(void *ptr);
extern void func_0209d340(void *ptr);
extern void func_020f5948(void *ptr);
extern Elem *data_021c8184;
extern int data_020dcd78;
extern void func_0200451c(void *);
extern int func_020044a0(void *);
extern void func_0205502c(void *);
extern void func_0209d090(void *);
extern int func_02055454(void *);
extern void func_0209d200(void *, void *);
extern int func_0209d180(void *p, unsigned int n, int a, int b, int c, int (*allocate)(int, int), void (*cleanup)(void),
                         void *context);
extern int func_0205c8f8(int size, int heapword);
extern void func_0205c8dc(void);
extern int data_020dcef0;
extern void func_02055124(void *addr);
extern int func_0209d088(void *addr);
extern void NNS_G3dMdlSetMdlAlpha(int r, int a, int b);
extern void func_020044d0(void *a, int *b);
extern int func_02056f28(void *addr, int x);
extern int func_020044c0(void *a, int b, int c, int d);
extern char data_021fbe48[];
extern int func_0203f8d0(Vec3 *d, Vec3 *s);
extern void func_020e96c8(char *g, int x, int y, int z);
extern void func_020e9774(char *g, int a);
extern void func_020e97a4(char *g, int a, int b, int c);
extern void func_020e9744(char *g, int a);
extern void func_020e9714(char *g, int a);
extern const char data_020dce90[];
extern const char data_020dcea8[];
extern const char data_020dcec0[];
extern const char data_020dced8[];
extern void *func_0209d238(void *, int *);
extern int func_02064328(char *, const char *, ...);
extern int func_0209d0ac(void *, void *, char *);
extern int func_02055f2c(void *, void *, int);
extern void *func_0209d324(void *);
extern void *func_02064b2c(char *, void *, int, int);
extern int NNS_G3dGetJntAnmSet(int resource);
extern int func_02107b44(int, int);
extern int func_02055140(void *, void *);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern int data_020dcd84[];
extern void *data_020dcd74;
extern void *data_020dcd70;
extern void func_0205510c(void *a, void *b);
extern int func_0209d138(unsigned int);
extern UnkStruct_0204ff00 data_020dce10[];
extern unsigned char data_020e54a8;
extern unsigned char data_020dce11[];
extern UnkStruct_0204feac data_020dce14[];
extern UnkStruct_0204feac data_020dce18[];

void *func_0205072c(void *self);
struct UnkStruct_02050704 *func_02050704(struct UnkStruct_02050704 *self);
void func_02050394(UnkStruct_02050394 *a0, UnkStruct_02050394_2 *self);
int func_0205027c(void *p0, void *p1, UnkStruct_0205027c *s);
int func_02050210(void *a, void *b, void *c);
int func_02050140(void *a, void *b, UnkStruct_02050140 *s);
void func_0204ff00(unsigned int a, unsigned int v, int b, int d, int e);
int func_0204fee8(unsigned int index);

void func_0205084c(const signed char *src, int arg1)
{
    int v1;
    int v2;
    char buf[5];
    signed char b;

    b = src[1];
    MI_CpuCopy8(src + 2, buf, 5);
    func_02077978(buf, &v1, &v2);
    func_0204ff00((unsigned char) arg1, 0, b, v1, v2);
}

void func_02050830(int a, int b)
{
    int local = 0;
    func_0204ff00((unsigned char) b, 1, -1, 0, local);
}

void func_02050814(int a, int b)
{
    func_0204ff00((unsigned char) b, 2, -1, 0, 0);
}

void *func_020507b8(void)
{
    UnkStruct_020507b8 *p = (UnkStruct_020507b8 *) func_020edf70(0x618);
    if (p != 0) {
        func_020ee660(p);
        p->unk_00 = (void *) data_020da13c;
        p->unk_00 = (void *) data_020dce48;
        __cxa_vec_ctor((void *) (&p->unk_50), 4, 0x16c, (((void (*)(void *)) func_0205072c)),
                       (((void (*)(void *))(void *(*) (void *) ) func_02050704)));
        func_0209d2b8(&p->unk_600);
    }
    return p;
}

void *func_0205072c(void *self)
{
    char *b = (char *) self;
    func_020f5958(b);
    func_0209d34c(b + 0x48);
    func_0209d11c(b + 0x4c);
    func_02055210(b + 0x98);
    *(int *) (b + 0x40) = -1;
    *(int *) (b + 0x44) = 0;
    func_0209d0a4(b + 0x4c);
    *(int *) (b + 0x8c) = 0x1000;
    *(int *) (b + 0x90) = 0x1000;
    *(int *) (b + 0x94) = 0x1000;
    *(int *) (b + 0x150) = 0x1000;
    *(int *) (b + 0x154) = 0x1000;
    *(int *) (b + 0x158) = 0x1000;
    *(short *) (b + 0x15c) = 0;
    *(short *) (b + 0x15e) = 0;
    *(short *) (b + 0x160) = 0;
    *(int *) (b + 0x164) = 0x1f;
    return self;
}

struct UnkStruct_02050704 *func_02050704(struct UnkStruct_02050704 *self)
{
    func_020551e0(self->unk_98);
    func_0209d104(self->unk_4C);
    func_0209d340(self->unk_48);
    func_020f5948(self);
    return self;
}

int func_020506c0(void)
{
    int result;
    int i;
    Elem *p;
    int count;

    i = 0;
    result = -1;
    p = data_021c8184;
    if (p) {
        p = (Elem *) ((char *) p + 0x50);
        count = data_020dcd78;
        while (i < count) {
            if (p->unk_44 == 0) {
                result = i;
                p->unk_44 = 1;
                break;
            }
            p = (Elem *) ((char *) p + 0x16c);
            i++;
        }
    }
    return result;
}

int func_0205066c(void *p0, int idx)
{
    int result = 0;
    if ((*(Elem_0205066c **) &data_021c8184) == 0) {
        return result;
    }
    if (idx == -1) {
        goto ret0;
    }
    {
        char *base = (char *) (*(Elem_0205066c **) &data_021c8184) + 0x50;
        Elem_0205066c *e = (Elem_0205066c *) (base + idx * 0x16c);
        e->unk_44 = 2;
        func_0209d238((char *) p0 + 0x600, (int *) ((char *) e + 0x48));
        func_0209d0a4((char *) ((char *) e + 0x4c));
        func_0200451c(e);
        result = 1;
    }
ret0:
    return result;
}

void func_020505f4(int arg0, int arg1)
{
    char *base;
    UnkStruct_020505f4 *e;
    int v;

    if (arg1 < 0) {
        return;
    }
    if (arg1 >= data_020dcd78) {
        return;
    }
    if ((*(char **) &data_021c8184) == 0) {
        return;
    }

    base = (*(char **) &data_021c8184) + 0x50;
    e = (UnkStruct_020505f4 *) (base + arg1 * 0x16c);

    v = e->unk_44;
    if (v != 0 && v != 1) {
        func_020044a0(e);
    }

    e->unk_40 = -1;
    e->unk_44 = 0;

    func_0205502c(&e->unk_98);
    func_0209d090(&e->unk_4C);
    func_02055454(&e->unk_98);
    func_0209d200((void *) (arg0 + 0x600), &e->unk_48);
}

int func_02050588(struct Param *param)
{
    if (param->state == 0) {
        data_020dcd78 = 4;
    } else if (param->state == 1) {
        data_020dcd78 = 1;
    }
    func_0209d180((char *) param + 0x600, data_020dcd78, 0x800, 0x80, 0x134c, func_0205c8f8, func_0205c8dc, &data_020dcef0);
    (*(struct Param **) &data_021c8184) = param;
    return 1;
}

int func_02050444(void *self)
{
    Entry *entry;
    int i, a, b, zero;
    int tmp[3], *ptr;

    if ((*(Entry **) &data_021c8184) == 0) {
        return 0;
    }
    entry = (Entry *) ((char *) (*(Entry **) &data_021c8184) + 0x50);
    i = 0;
    a = 0;
    b = 0;
    zero = 0;

    while (i < data_020dcd78) {
        switch (entry->unk_44) {
            case 0:
                break;
            case 1:
                if (entry->unk_40 != ~zero) {
                    func_0205066c(self, i);
                }
                break;
            case 2:
                if ((unsigned) (entry->unk_40 - 0x38) <= 2) {
                    func_02050210(self, (char *) self + 0x600, (void *) entry);
                } else if (entry->unk_40 == 0x3b) {
                    func_02050140(self, (char *) self + 0x600, (UnkStruct_02050140 *) entry);
                } else {
                    func_0205027c(self, (char *) self + 0x600, (UnkStruct_0205027c *) entry);
                }
                break;
            case 3:
                if (entry->unk_40 == 0x3b) {
                    func_02055124((char *) entry + 0x98);
                    NNS_G3dMdlSetMdlAlpha(func_0209d088((char *) entry + 0x4c), a, entry->unk_164);
                } else {
                    if (entry->unk_40 != 0x38 && entry->unk_40 != 0x39 && entry->unk_40 != 0x3a) {
                        func_02055124((char *) entry + 0x98);
                        if (entry->unk_169 != 0) {
                            ptr = entry->unk_8C;
                            tmp[0] = ptr[0];
                            tmp[1] = ptr[1];
                            tmp[2] = ptr[2];
                            func_020044d0(entry, tmp);
                            if (func_02056f28((char *) entry + 0x134, 1) != 0) {
                                func_020044c0(entry, 0x84d, 0x7f, b);
                            }
                        }
                    }
                }
                func_02050394((UnkStruct_02050394 *) self, (UnkStruct_02050394_2 *) entry);
                break;
            case 4:
                func_020505f4((int) self, i);
                break;
            default:
                break;
        }
        entry = (Entry *) ((char *) entry + 0x16c);
        i++;
    }
    return 1;
}

void func_02050394(UnkStruct_02050394 *a0, UnkStruct_02050394_2 *self)
{
    Vec3 a;
    Vec3 b;
    Vec3 *q;
    char *m;
    int k;
    int mode;
    int r;

    m = (char *) self + 0x98;
    k = self->unk_40;
    q = &self->unk_8C;
    a.x = self->unk_8C.x;
    a.y = q->y;
    a.z = q->z;
    mode = a0->unk_08;
    if (mode == 0) {
        r = func_0203f8d0(&b, &a);
    } else if (mode == 1) {
        r = 0;
        b.x = a.x;
        b.y = a.y;
        b.z = a.z;
    }
    func_020e96c8(data_021fbe48, b.x, b.y, b.z);
    func_020e9774(data_021fbe48, r);
    if (k != 0xf) {
        func_020e97a4(data_021fbe48, self->unk_15C, self->unk_15E, self->unk_160);
    } else {
        func_020e9744(data_021fbe48, self->unk_15E);
        func_020e9714(data_021fbe48, self->unk_160);
        func_020e9774(data_021fbe48, self->unk_15C);
    }
    m = m + 0x64;
    *(Mtx *) m = *(Mtx *) data_021fbe48;
}

int func_0205027c(void *p0, void *p1, UnkStruct_0205027c *s)
{
    int ret;
    void *a;
    void *c;
    void *q;
    char buf[0x18];
    int n;
    int t;
    void *r;
    int flags;

    ret = 0;
    if (p1 == 0 || s == 0) {
        return 0;
    }
    n = s->unk_40;
    a = func_0209d238(p1, &s->unk_48);
    q = &s->unk_4C;
    t = n / 0x10;
    if (n < 10) {
        func_02064328(buf, data_020dce90, t, n);
    } else {
        func_02064328(buf, data_020dcea8, t, n);
    }
    if (func_0209d0ac(q, a, buf)) {
        r = &s->unk_98;
        func_02055f2c(r, (void *) func_0209d088(q), 0);
        c = func_0209d324(a);
        if (n < 10) {
            func_02064328(buf, data_020dcec0, t, n);
        } else {
            func_02064328(buf, data_020dced8, t, n);
        }
        t = func_02107b44(NNS_G3dGetJntAnmSet((int) func_02064b2c(buf, c, 4, 0)), 0);
        flags = 0x1000;
        if (!s->unk_168) {
            flags = 0;
        }
        if (func_02055140(r, c)) {
            func_02055060(r, t, 0, flags, 1, 0);
            func_02055050(r);
            s->unk_44 = 3;
            func_02050394((UnkStruct_02050394 *) p0, (UnkStruct_02050394_2 *) s);
            ret = 1;
        }
    }
    return ret;
}

int func_02050210(void *a, void *b, void *c)
{
    int success = 0;
    int off, ret1, ret2;
    char *ptr;

    if (b == 0 || c == 0) {
        return 0;
    }

    off = *(int *) ((char *) c + 0x40);
    ret1 = (int) func_0209d238(b, (int *) ((char *) c + 0x48));
    ptr = (char *) c + 0x4c;

    if (func_0209d0ac(ptr, (void *) ret1, (char *) (data_020dcd84[off - 0x38]))) {
        ret2 = func_0209d088(ptr);
        func_02055f2c((char *) c + 0x98, (void *) ret2, 0);
        *(int *) ((char *) c + 0x44) = 3;
        func_02050394((UnkStruct_02050394 *) a, (UnkStruct_02050394_2 *) c);
        success = 1;
    }

    return success;
}

int func_02050140(void *a, void *b, UnkStruct_02050140 *s)
{
    int ret = 0;
    void *p;
    void *h;
    void *v;
    void *x;
    void *r4;
    int kind;

    if (b == 0 || s == 0) {
        return 0;
    }
    kind = s->unk_40;
    h = func_0209d238(b, &s->unk_48);
    p = s;
    p = &s->unk_4C;
    if (func_0209d0ac(p, h, (char *) data_020dcd74) != 0) {
        r4 = &s->unk_98;
        func_02055f2c(r4, (void *) func_0209d088(p), 0);
        v = func_0209d324(h);
        x = (void *) func_02107b44(
            (int) ((void *) NNS_G3dGetJntAnmSet((int) (func_02064b2c((char *) data_020dcd70, v, 4, 0)))), 0);
        if (func_02055140(r4, v) != 0) {
            func_02055060(r4, (int) x, 0, 0x1000, 1, 0);
            func_02055050(r4);
            s->unk_44 = 3;
            func_02050394((UnkStruct_02050394 *) a, (UnkStruct_02050394_2 *) s);
            if (kind == 0x3b) {
                NNS_G3dMdlSetMdlAlpha((int) ((void *) func_0209d088(p)), 0, s->unk_164);
            }
            ret = 1;
        }
    }
    return ret;
}

int func_020500d8(void)
{
    Entry_020500d8 *p;
    int i;
    int buf[3];

    if ((*(unsigned char **) &data_021c8184) == 0) {
        return 0;
    }

    p = (Entry_020500d8 *) ((*(unsigned char **) &data_021c8184) + 0x50);
    i = 0;
    while (i < data_020dcd78) {
        if (p->type == 3) {
            buf[0] = p->val0;
            buf[1] = p->val1;
            buf[2] = p->val2;
            func_0205510c(p->data, buf);
        }
        p = (Entry_020500d8 *) ((char *) p + 0x16c);
        i++;
    }
    return 1;
}

int func_0205009c(unsigned int param)
{
    int i;
    for (i = 0; i < data_020dcd78; i++) {
        func_020505f4(param, i);
    }
    func_0209d138(param + 0x600);
    (*(int *) &data_021c8184) = 0;
    return 1;
}

void func_0205007c(Dest *dst, Src *src)
{
    dst->unk_150 = src->unk_00;
    dst->unk_154 = src->unk_04;
    dst->unk_158 = src->unk_08;
}

void func_0204ff00(unsigned int a, unsigned int v, int b, int d, int e)
{
    int ok;

    if (a >= 4) {
        return;
    }
    if (b >= 0x38) {
        return;
    }
    switch (v) {
        case 0:
            data_020dce10[a].unk_00 = (unsigned char) v;
            data_020dce10[a].unk_01 = (unsigned char) b;
            data_020dce10[a].unk_04 = d;
            data_020dce10[a].unk_08 = e;
            break;
        case 3:
            data_020dce10[a].unk_00 = (unsigned char) v;
            break;
        case 1:
            switch (data_020e54a8) {
                case 0:
                    ok = 1;
                    break;
                default:
                    ok = 0;
                    break;
            }
            if (ok != 0) {
                if (func_0204fee8(a) == 3) {
                    data_020dce10[a].unk_00 = (unsigned char) v;
                } else {
                    data_020dce10[a].unk_00 = 8;
                }
                data_020dce10[a].unk_01 = (unsigned char) b;
                data_020dce10[a].unk_04 = d;
                data_020dce10[a].unk_08 = e;
            } else {
                data_020dce10[a].unk_00 = 8;
                data_020dce10[a].unk_01 = (unsigned char) b;
                data_020dce10[a].unk_04 = d;
                data_020dce10[a].unk_08 = e;
            }
            break;
        case 2:
            switch (data_020e54a8) {
                case 0:
                    ok = 1;
                    break;
                default:
                    ok = 0;
                    break;
            }
            if (ok != 0) {
                if (func_0204fee8(a) == 3 || func_0204fee8(a) == 8 || func_0204fee8(a) == 1) {
                    data_020dce10[a].unk_00 = (unsigned char) v;
                } else {
                    data_020dce10[a].unk_00 = 8;
                }
                data_020dce10[a].unk_01 = (unsigned char) b;
                data_020dce10[a].unk_04 = d;
                data_020dce10[a].unk_08 = e;
            } else {
                data_020dce10[a].unk_00 = 8;
                data_020dce10[a].unk_01 = (unsigned char) b;
                data_020dce10[a].unk_04 = d;
                data_020dce10[a].unk_08 = e;
            }
            break;
        case 4:
            data_020dce10[a].unk_00 = (unsigned char) v;
            break;
        case 5:
            data_020dce10[a].unk_00 = (unsigned char) v;
            break;
        case 8:
            data_020dce10[a].unk_00 = 8;
            data_020dce10[a].unk_01 = (unsigned char) b;
            data_020dce10[a].unk_04 = d;
            data_020dce10[a].unk_08 = e;
            break;
        case 6:
        case 7:
        default:
            data_020dce10[a].unk_00 = (unsigned char) v;
            break;
    }
}

int func_0204fee8(unsigned int index)
{
    if (index >= 4) {
        return 9;
    } else {
        return ((unsigned char *) data_020dce10)[index * 12];
    }
}

unsigned char func_0204fed0(unsigned int x)
{
    if (x >= 4) {
        return 0xFF;
    }
    return data_020dce11[x * 12];
}

int func_0204feac(int *out0, int *out1, unsigned int index)
{
    if (index >= 4) {
        return 0;
    }
    *out0 = data_020dce14[index].a;
    *out1 = data_020dce18[index].a;
    return 1;
}

int func_0204fea4(void)
{
    return func_020506c0();
}
