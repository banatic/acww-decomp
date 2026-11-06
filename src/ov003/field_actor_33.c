/* field_actor_33: 14 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221474c @ 0x0221474c, 0x454 bytes, Thumb
 * func_ov003_022146fc @ 0x022146fc, 0x50 bytes, Thumb
 * func_ov003_022146bc @ 0x022146bc, 0x40 bytes, Thumb
 * func_ov003_02214644 @ 0x02214644, 0x78 bytes, Thumb
 * func_ov003_02214604 @ 0x02214604, 0x40 bytes, Thumb
 * func_ov003_022145f8 @ 0x022145f8, 0xc bytes, Thumb
 * func_ov003_022145b0 @ 0x022145b0, 0x48 bytes, Thumb
 * func_ov003_022145a0 @ 0x022145a0, 0x10 bytes, Thumb
 * func_ov003_02214568 @ 0x02214568, 0x38 bytes, Thumb
 * func_ov003_02214384 @ 0x02214384, 0x1e4 bytes, Thumb
 * func_ov003_02214200 @ 0x02214200, 0x184 bytes, Thumb
 * func_ov003_022140a8 @ 0x022140a8, 0x158 bytes, Thumb
 * func_ov003_02213f74 @ 0x02213f74, 0x134 bytes, Thumb
 * func_ov003_02213ec0 @ 0x02213ec0, 0xb4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    int a[9];
    Vec pos;
} Blk;

typedef struct {
    u16 a, b, c, d;
} Msg;

typedef struct {
    u8 pad_00[0x7e];
    char unk_7E;
    u8 pad_7F[0x1ff - 0x7f];
    u8 unk_1FF;
} Actor;

typedef struct {
    u8 pad_00[0xec];
    u8 unk_EC[0x2d0 - 0xec];
    u8 unk_2D0[0x2d8 - 0x2d0];
    int unk_2D8;
    u8 pad_2DC[0x5a0 - 0x2dc];
    u8 unk_5A0[0x5c8 - 0x5a0];
    u8 unk_5C8[0x698 - 0x5c8];
    Blk unk_698;
    u8 pad_6C8[0x704 - 0x6c8];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    u8 unk_7D4[2];
    u8 pad_7D6[0x7f0 - 0x7d6];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x810 - 0x804];
    int unk_810;
    u8 pad_814[0x81c - 0x814];
    int unk_81C;
    u8 pad_820[0x8f0 - 0x820];
    u8 unk_8F0[4];
} UnkStruct_0221474c;

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x5a0 - 0x2d4];
    int unk_5A0;
    char pad_5A4[0x7f0 - 0x5a4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
} UnkStruct_022146fc;

struct UnkStruct_022146bc {
    char pad_00[0x800];
    int unk_800;
};

typedef struct UnkStruct_02214644_2 {
    char pad_00[0xc];
    short unk_0C;
    char pad1[0x1c - 0xc - 2];
} UnkStruct_02214644_2;

typedef struct UnkStruct_02214644 {
    char pad_00[0x8e];
    short unk_8E;
    char pad1[0x144 - 0x90];
    int unk_144;
    char pad_148[0x14c - 0x148];
    int unk_14C;
    char pad_150[0x154 - 0x150];
    int unk_154;
    char pad_158[0x6f4 - 0x158];
    int unk_6F4;
    char pad_6F8[0x6fc - 0x6f8];
    int unk_6FC;
} UnkStruct_02214644;

typedef struct {
    char unk_00;
    char pad_01;
    short unk_02;
    unsigned char unk_04;
} Sub7D4;

typedef struct {
    char pad_00[0x7d4];
    Sub7D4 sub;
} UnkStruct_02214604;

typedef struct {
    int x, y, z;
} Vec_02214384;

struct S7d4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
};

struct UnkStruct_02214384 {
    u8 pad_00[0x2d0];
    u8 unk_2D0[8];
    struct {
        unsigned int : 12;
        unsigned int f16 : 16;
        unsigned int : 4;
    } bf;
    u32 pad_2DC;
    u32 unk_2E0;
    u8 pad_2E4[0x68c - 0x2e4];
    int unk_68C, unk_690, unk_694;
    u8 pad_698[0x7d4 - 0x698];
    struct S7d4 unk_7D4;
};

struct St {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    volatile unsigned short id;
};

typedef struct {
    int x, y, z;
} Vec_02214200;

typedef struct {
    int m[4][3];
} Mtx43;

typedef struct UnkStruct_02214200 UnkStruct_02214200;

struct UnkStruct_02214200 {
    char pad_00[0x5c];
    Vec_02214200 unk_5C;
    char pad_68[0x8e - 0x68];
    u16 unk_8E;
    char pad_90[0x2d8 - 0x90];
    unsigned int unk_2D8;
    char pad_2DC[0x608 - 0x2dc];
    Mtx43 unk_608;
};

extern u8 data_ov003_0223c026[];
extern void *data_020ccf94;
extern const int data_ov003_02238104;
extern const int data_ov003_02238108;
extern Actor *func_020604f8(void *);
extern void func_ov003_02219668(Blk *, int);
extern int func_0203f7d0(Vec *, Vec *);
extern int func_ov003_0222aa50(Actor *, Vec *, Vec *);
extern int func_ov003_0222a8a8(int);
extern int func_02056f94(void *);
extern int func_02008258(UnkStruct_0221474c *, int);
extern int func_0200d4e8(UnkStruct_0221474c *, int, int, int);
extern int func_02073908(void *, int);
extern int func_0209a110(u16 *);
extern void func_02060460(void *);
extern void func_020109fc(UnkStruct_0221474c *, int, int, int);
extern void func_0205eae0(void *, int, int, int);
extern int func_0206f6f8(int, Actor *);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void func_020604fc(void *, int);
extern int func_0200f290(UnkStruct_0221474c *, int);
extern void func_0200f268(UnkStruct_0221474c *, int);
extern void func_0203ee08(UnkStruct_0221474c *, void *);
extern int func_0203e19c(void);
extern u16 func_0206f6a4(void);
extern int func_ov003_0220d498(UnkStruct_0221474c *, const void *, int, int, int);
extern int func_02043554(int, u16);
extern void func_ov003_0222aaa0(Vec *, int);
extern void func_ov003_02214c00(void *, int);
extern void func_02060448(void *);
extern int func_ov003_02214bfc(void *);
extern void func_02010f5c(void *);
extern int func_0200f554(void *);
extern void func_02010d64(void *);
extern unsigned int func_0200e92c(UnkStruct_02214644_2 *local);
extern void func_0200e90c(UnkStruct_02214644_2 *local, int x, int y, int z);
extern int func_020e8ed8(int a, int b);
extern int func_0200e894(UnkStruct_02214644 *s, UnkStruct_02214644_2 *local);
extern int func_0200e91c(UnkStruct_02214644_2 *local);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern int func_0200f328(void *ptr, int off);
extern void func_0200fb34(void *self, short value);
extern void func_0200fa6c(void *dst, void *src);
extern void func_02010d88(void *dst, void *src, int a, int b);
extern void func_02089fc8(void *dst);
extern void func_020110c4(volatile unsigned short *p, struct UnkStruct_02214384 *self);
extern int func_020899a8(Vec_02214384 *a, Vec_02214384 *b, int d, u8 *out, int e);
extern int func_ov003_0222f458(Vec_02214384 *v, u8 k);
extern u8 func_ov003_0222f490(u8 k);
extern int func_ov003_0222e3a4(u8 k);
extern int func_ov003_02213da0(struct UnkStruct_02214384 *p, Vec_02214384 *a, Vec_02214384 *src, Vec_02214384 *dst);
extern int func_020e8b4c(int a, int b);
extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];
extern int func_02056f28(void *p, int a);
extern int func_ov003_0220c934(void *p);
extern unsigned int *func_0200f27c(void *p, int a);
extern void func_0200fa1c(void *out, void *self, void *b, void *c, void *d);
extern void func_0204f7e0(void *a, void *b);
extern int func_020310d0(void *a, void *b, int c);
extern unsigned char data_ov003_0223811c[];
extern unsigned char data_ov003_02238120[];
extern void *data_021c80bc;
extern unsigned short *func_0204f5a8(void *ctx, void *p, int k);
extern char data_ov003_02238114[];

void func_ov003_02214200(UnkStruct_02214200 *self, Vec_02214200 *p1, Vec_02214200 *p2, Vec_02214200 *p3);
int func_ov003_022140a8(char *self, unsigned char *flag, int *a, int *b);
int func_ov003_02213f74(char *self, int *a, int *b, unsigned char *flag);

void func_ov003_0221474c(UnkStruct_0221474c *self)
{
    Msg m;
    Vec c;
    Blk blk;
    Vec v48;
    Vec v54;
    Vec v60;
    Vec v6c;
    Vec v78;
    Vec v84;
    Vec v90;
    Actor *act;
    int v;
    int a2;
    u8 *st;
    void *sub;
    unsigned int ok;
    u16 hi, lo;
    void *bp;

    act = func_020604f8(self->unk_5C8);
    if (self->unk_704 == 0x5a) {
        v = self->unk_2D8 >> 12;
        if ((u16) v < 6) {
            if (act != 0) {
                a2 = (data_ov003_0223c026[act->unk_1FF * 0x14] << 12) / 0x64;
                v = (s16) (a2 - a2 * (u16) v / 6);
            } else {
                v = (s16) (0x1000 - 0x2ab * (u16) v);
            }
        } else {
            v = 0;
        }
    } else {
        v = 0;
    }
    c.x = v;
    c.y = v;
    c.z = v;
    blk = self->unk_698;
    func_ov003_02219668(&blk, 0);
    v48.x = blk.pos.x;
    v48.y = blk.pos.y;
    v48.z = blk.pos.z;
    m.a = 0xfff1;
    if (act != 0) {
        func_0203f7d0(&v48, &v48);
        v54.x = v48.x;
        v54.y = v48.y;
        v54.z = v48.z;
        v60.x = c.x;
        v60.y = c.y;
        v60.z = c.z;
        func_ov003_0222aa50(act, &v54, &v60);
        m.a = (u16) (act->unk_7E + 0x12e8);
        if (v == 0) {
            func_ov003_0222a8a8(self->unk_800);
        }
    }
    st = self->unk_7D4;
    sub = self->unk_8F0;
    switch (st[0]) {
        case 0:
            if (func_02056f94(self->unk_2D0) == 0) {
                break;
            }
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 6, 1, -1);
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                m.d = m.a;
                func_0209a110(&m.d);
            }
            func_02060460(self->unk_5C8);
            break;
        case 1:
            if (self->unk_704 == 0x5a) {
                if (func_02056f94(self->unk_2D0) == 0) {
                    break;
                }
                func_020109fc(self, 0x6c, 6, 6);
                func_0205eae0(self->unk_5A0, 0x13, 6, 0);
            }
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                if (self->unk_81C == 5) {
                    if (func_0206f6f8(m.a, act) == 0) {
                        break;
                    }
                    self->unk_81C = 6;
                    break;
                }
                if (self->unk_81C == 6) {
                    if (func_0206fbc0() == 0) {
                        break;
                    }
                    self->unk_81C = 0xf;
                    if (func_0206fc6c() != 0) {
                        func_020604fc(self->unk_5C8, 0);
                        if (func_0200f290(self, 0x11) != 0) {
                            func_0200f268(self, 0x11);
                            bp = (char *) self;
                            if (self != 0) {
                                bp = (char *) bp + 0xec;
                            }
                            func_0203ee08(self, bp);
                        }
                        func_0203e19c();
                        m.b = func_0206f6a4();
                        self->unk_7FC = func_02008258(self, self->unk_7F0);
                        ok = 0;
                        hi = *(volatile u16 *) &m.b;
                        lo = *(volatile u16 *) &m.b;
                        if (lo >= 0x12e8 && hi <= 0x131f) {
                            ok = 1;
                        }
                        if (ok != 0) {
                            func_ov003_0220d498(self, &data_ov003_02238104, 0, 6, -1);
                            break;
                        }
                        func_0200d4e8(self, 6, 1, -1);
                        st[0] = 2;
                        break;
                    }
                } else if (self->unk_81C < 0xf) {
                    break;
                }
                ok = 0;
                hi = *(volatile u16 *) &m.a;
                lo = *(volatile u16 *) &m.a;
                if (lo >= 0x1320 && hi <= 0x1322) {
                    ok = 1;
                }
                if (ok != 0) {
                    st[0] = 3;
                    if (self->unk_810 == -1) {
                        self->unk_810 = func_02043554(self->unk_800, m.a);
                        if (self->unk_810 != -1) {
                            st[0] = 2;
                        }
                    }
                } else {
                    if (act != 0) {
                        func_ov003_0222aaa0(&c, act->unk_7E);
                        v6c.x = v48.x;
                        v6c.y = v48.y;
                        v6c.z = v48.z;
                        v78.x = c.x;
                        v78.y = c.y;
                        v78.z = c.z;
                        func_ov003_0222aa50(act, &v6c, &v78);
                    }
                    func_ov003_0220d498(self, &data_ov003_02238108, 0, 6, -1);
                    func_ov003_02214c00(sub, 2);
                }
                func_02060448(self->unk_5C8);
                if (func_0200f290(self, 0x11) != 0) {
                    func_0200f268(self, 0x11);
                    bp = (char *) self;
                    if (self != 0) {
                        bp = (char *) bp + 0xec;
                    }
                    func_0203ee08(self, bp);
                }
                func_0203e19c();
                break;
            }
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            if (func_ov003_02214bfc(sub) == 2) {
                if (act != 0) {
                    func_ov003_0222aaa0(&c, act->unk_7E);
                    v84.x = v48.x;
                    v84.y = v48.y;
                    v84.z = v48.z;
                    v90.x = c.x;
                    v90.y = c.y;
                    v90.z = c.z;
                    func_ov003_0222aa50(act, &v84, &v90);
                }
                func_02060448(self->unk_5C8);
                st[0] = 2;
                func_020109fc(self, 0, 6, 6);
            }
            break;
        case 2:
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 6, 1, -1);
            break;
        case 3:
            if (self->unk_810 == -1) {
                self->unk_810 = func_02043554(self->unk_800, m.a);
                if (self->unk_810 != -1) {
                    st[0] = 2;
                }
            }
            break;
    }
}

void func_ov003_022146fc(UnkStruct_022146fc *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258((UnkStruct_0221474c *) self, self->unk_7F0);
        func_020109fc((UnkStruct_0221474c *) self, 0x6c, 6, 6);
        func_0205eae0(&self->unk_5A0, 0x13, 6, 0);
    }
}

void func_ov003_022146bc(struct UnkStruct_022146bc *arg)
{
    func_02010f5c(arg);
    func_0200f554(arg);
    func_02010d64(arg);
    if (func_02073908((void *) ((*(int *) &data_020ccf94)), arg->unk_800) != 0) {
        func_ov003_0221474c((UnkStruct_0221474c *) arg);
    } else {
        func_ov003_022146fc((UnkStruct_022146fc *) arg);
    }
}

int func_ov003_02214644(UnkStruct_02214644 *s, int a, int b)
{
    UnkStruct_02214644_2 local;
    short *p;
    int result;

    func_0200e92c(&local);
    p = &local.unk_0C;
    func_0200e90c(&local, 0x56, a, b);

    if (s->unk_144 == 2) {
        *p = (short) func_020e8ed8(s->unk_14C - s->unk_6F4, s->unk_154 - s->unk_6FC);
    } else {
        *p = s->unk_8E;
    }

    result = func_0200e894(s, &local);
    func_0200e91c(&local);

    return result;
}

void func_ov003_02214604(UnkStruct_02214604 *self, char *other, int previous)
{
    int idx = 0xc;
    Sub7D4 *p = &self->sub;
    p->unk_00 = 0;
    p->unk_02 = *(short *) (other + idx);
    p->unk_04 = 0xff;
    func_020109a0(self, 0x5b, 3, 0);
    func_0205eae0((char *) self + 0x5a0, 3, 3, 0);
}

void func_ov003_022145f8(int a, int b)
{
    func_ov003_02214644((UnkStruct_02214644 *) a, 6, b);
}

void func_ov003_022145b0(char *p)
{
    int r5;

    r5 = (func_02056f94((char *) p + 0x2d0) != 0);
    func_02010f5c(p);
    if (r5 == 0) {
        if (func_02056f94((char *) p + 0x2d0) != 0) {
            func_0200f328(p, 0x848);
        }
    }
}

void func_ov003_022145a0(void *self)
{
    func_0200fb34(self, *(short *) ((char *) self + 0x7d6));
}

void func_ov003_02214568(void *arg0)
{
    char local[16];
    func_0200fa6c(local, arg0);
    func_02010d88(arg0, local, 0x99a, 0x1000);
    func_02089fc8((char *) arg0 + 0x1c4);
}

void func_ov003_02214384(struct UnkStruct_02214384 *self)
{
    struct St st;
    Vec_02214384 va, vb, vc, vd;
    struct {
        Vec_02214384 a;
        Vec_02214384 b;
    } pr;
    Vec_02214384 vf;
    struct S7d4 *s7;
    unsigned int ok;
    unsigned short hv, lv;
    int r;

    if (self->unk_2E0 == 0) {
        return;
    }
    if (func_02056f94(self->unk_2D0) != 0) {
        return;
    }
    if (self->bf.f16 < 3) {
        return;
    }

    st.a = 0;
    st.b = 0;

    {
        int t2 = self->unk_694, t1 = self->unk_690, t0 = self->unk_68C;
        va.x = t0;
        va.y = t1;
        va.z = t2;
    }
    func_0203f7d0((Vec *) (&va), (Vec *) (&va));
    vb.x = va.x;
    vb.y = va.y;
    vb.z = va.z;
    func_ov003_02214200((UnkStruct_02214200 *) self, (Vec_02214200 *) (&vb), (Vec_02214200 *) (&vc), (Vec_02214200 *) (&vd));

    s7 = &self->unk_7D4;
    if (s7->unk_00 == 0 && self->bf.f16 < 6) {
        func_020110c4(&st.id, self);
        ok = 0;
        hv = st.id;
        lv = st.id;
        if (lv >= 0x1376 && hv <= 0x1376) {
            ok = 1;
        }
        if (func_020899a8(&vb, &vc, ok ? 0xa00 : 0xd1f, &st.c, 0) != 0) {
            st.a = 1;
            func_ov003_0222f458((Vec_02214384 *) &pr, st.c);
            st.b = func_ov003_0222f490(st.c);
            if (st.b != 0) {
                pr.a.z = pr.a.z + 0x100;
            }
        }
    }

    switch ((unsigned int) func_ov003_022140a8((char *) self, (unsigned char *) (&st), (int *) ((Vec_02214384 *) &pr),
                                               (int *) (&st.b))) {
        case 1:
            if (func_ov003_0222e3a4(st.c) != 0) {
                s7->unk_00 = 1;
                s7->unk_04 = st.c;
                func_0200f328((void *) self, 0x847);
            }
            break;
        case 2:
            return;
        case 3:
            if (s7->unk_00 != 0) {
                break;
            }
            s7->unk_00 = 1;
            s7->unk_04 = 0xff;
            func_0200f328((void *) self, 0x847);
            break;
        case 0:
        default:
            vf.x = va.x;
            vf.y = va.y;
            vf.z = va.z;
            r = func_ov003_02213da0(self, &vf, &vc, &vd);
            if (st.a == 0) {
                break;
            }
            if (r != 0) {
                pr.b.x = pr.a.x - vd.x;
                pr.b.z = pr.a.z - vd.z;
                r = func_020e8ed8(pr.b.x, pr.b.z);
            } else {
                r = 0x7fff;
            }
            if (func_020e8b4c(r, 0) > 0x4000) {
                if (func_ov003_0222e3a4(st.c) != 0) {
                    s7->unk_00 = 1;
                    s7->unk_04 = st.c;
                    func_0200f328((void *) self, 0x847);
                }
            }
            break;
    }
}

void func_ov003_02214200(UnkStruct_02214200 *self, Vec_02214200 *p1, Vec_02214200 *p2, Vec_02214200 *p3)
{
    Vec_02214200 *v;
    int t, s, c;
    unsigned int kind;
    Mtx43 m;
    Vec_02214200 w;

    v = &self->unk_5C;
    p2->x = v->x;
    p2->y = v->y;
    p2->z = v->z;

    t = (self->unk_8E >> 4) << 1;
    s = FX_SinCosTable_[t];
    c = FX_SinCosTable_[t + 1];

    kind = (self->unk_2D8 << 4) >> 16;
    switch (kind) {
        case 3:
            func_0200f328((void *) self, 0x845);
            p1->y = p1->y + 0x1dd3;
            p2->x = p2->x + FX_MulFunc(s, 0x1e66);
            p2->y = p2->y + 0x24cd;
            p2->z = p2->z + FX_MulFunc(c, 0x1e66);
            break;
        case 4:
            p1->x = v->x;
            p1->y = v->y;
            p1->z = v->z;
            p1->x = p1->x + FX_MulFunc(s, 0x1e66);
            p1->y = p1->y + 0x24cd;
            p1->z = p1->z + FX_MulFunc(c, 0x1e66);
            p2->x = p2->x + FX_MulFunc(s, 0x2a66);
            p2->z = p2->z + FX_MulFunc(c, 0x2a66);
            break;
        case 5:
            p1->x = v->x;
            p1->y = v->y;
            p1->z = v->z;
            p1->x = p1->x + FX_MulFunc(s, 0x2a66);
            p1->z = p1->z + FX_MulFunc(c, 0x2a66);
            p2->x = p2->x + FX_MulFunc(s, 0x2800);
            p2->y = p2->y - 0x666;
            p2->z = p2->z + FX_MulFunc(c, 0x2800);
            break;
    }
    m = self->unk_608;
    w.x = m.m[3][0];
    w.y = m.m[3][1];
    w.z = m.m[3][2];
    func_0203f7d0((Vec *) (&w), (Vec *) (&w));
    p3->x = w.x;
    p3->y = w.y;
    p3->z = w.z;
}

int func_ov003_022140a8(char *self, unsigned char *flag, int *a, int *b)
{
    int hash1;
    int hash2;
    int buf1[3];
    int buf2[3];

    if (func_02056f28(self + 0x2d0, 4) != 0) {
        if (func_ov003_0220c934(self) != 0) {
            func_0200f27c(self, 9);
            func_0200f328(self, 0x846);
            *(int *) (self + 0x2e0) = 0;
            func_0205eae0(self + 0x5a0, 4, 3, 1);
            if (*(unsigned char *) (self + 0x16c) == 4) {
                return 3;
            }
            if (*flag != 0) {
                return 1;
            }
            return 2;
        }
        func_0200fa1c(buf1, self, self + 0x5c, self + 0x8e, (void *) data_ov003_0223811c);
        func_0204f7e0(buf1, buf1);
        if (func_020310d0(buf1, &hash1, 0x19) >= 0x400) {
            func_0200f27c(self, 9);
            func_0200f328(self, 0x846);
            *(int *) (self + 0x2e0) = 0;
            func_0205eae0(self + 0x5a0, 4, 3, 1);
            if (*flag != 0) {
                if (func_ov003_02213f74((char *) self, (int *) buf1, (int *) a, (unsigned char *) b) != 0) {
                    return 1;
                }
                return 2;
            }
            return 2;
        }
    } else if (func_02056f28(self + 0x2d0, 3) != 0) {
        if (*flag != 0) {
            func_0200fa1c(buf2, self, self + 0x5c, self + 0x8e, (void *) data_ov003_02238120);
            func_0204f7e0(buf2, buf2);
            if (func_020310d0(buf2, &hash2, 0x19) >= 0x400) {
                if (func_ov003_02213f74((char *) self, (int *) buf2, (int *) a, (unsigned char *) b) != 0) {
                    return 1;
                }
                return 2;
            }
        }
    }
    return 0;
}

int func_ov003_02213f74(char *self, int *a, int *b, unsigned char *flag)
{
    int *p;
    volatile int pos[3];
    unsigned short *o;
    unsigned short v;
    int a1, a2;
    int bz, pz;
    int dx, dz;
    int d;
    short c;
    int t;

    p = (int *) (self + 0x5c);
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    o = func_0204f5a8(data_021c80bc, a, 0);
    if (o != 0) {
        v = *o;
        if (v == 0x1b || v == 0x89) {
            return 1;
        }
    }
    if (*flag == 0) {
        a1 = func_020e8ed8(b[0] - pos[0], b[2] - pos[2]);
        a2 = func_020e8ed8(a[0] - pos[0], a[2] - pos[2]);
        a1 = (short) func_020e8b4c(a1, 0);
        a2 = (short) func_020e8b4c(a2, 0);
        if (a1 == a2) {
            bz = b[2];
            pz = pos[2];
            if ((pz >= bz && bz > a[2]) || (pz <= bz && bz < a[2])) {
                return 1;
            }
            return 0;
        }
        if ((a1 >= 0x4000 && a2 > a1) || (a2 < 0x4000 && a2 <= a1)) {
            return 1;
        }
        dx = a[0] - pos[0];
        dz = a[2] - pos[2];
        d = dx * dx + dz * dz;
        c = FX_SinCosTable_[((unsigned short) (short) (a1 - a2) >> 4) * 2 + 1];
        t = FX_MulFunc(d, (short) c);
        t = FX_MulFunc(t, (short) c);
        if (d - t < 0x900000) {
            return 0;
        }
        return 1;
    }
    bz = b[2];
    pz = pos[2];
    if ((pz >= bz && bz > a[2]) || (pz <= bz && bz < a[2])) {
        return 1;
    }
    return 0;
}

int func_ov003_02213ec0(char *self)
{
    int len;
    char buf[12];

    if (func_02056f28(self + 0x2d0, 4) == 0) {
        goto fail;
    }
    if (func_ov003_0220c934(self) == 0) {
        goto else_block;
    }

    func_0200f27c(self, 9);
    func_0200f328(self, 0x846);
    *(int *) (self + 0x2e0) = 0;
    func_0205eae0(self + 0x5a0, 4, 3, 1);
    return 1;

else_block:
    func_0200fa1c(buf, self, self + 0x5c, self + 0x8e, data_ov003_02238114);
    if (func_020310d0(buf, &len, 0x19) < 0x400) {
        goto fail;
    }

    func_0200f27c(self, 9);
    func_0200f328(self, 0x846);
    *(int *) (self + 0x2e0) = 0;
    func_0205eae0(self + 0x5a0, 4, 3, 1);
    return 1;

fail:
    return 0;
}
