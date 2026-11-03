/* mabel_talk_2: 10 functions, module ov049
 * mwccarm 1.2/base -O4,s
 * func_ov049_022617b4 @ 0x022617b4, 0x94 bytes, Thumb
 * func_ov049_02261764 @ 0x02261764, 0x50 bytes, Thumb
 * func_ov049_0226171c @ 0x0226171c, 0x48 bytes, Thumb
 * func_ov049_02261680 @ 0x02261680, 0x9c bytes, Thumb
 * func_ov049_0226166c @ 0x0226166c, 0x14 bytes, Thumb
 * func_ov049_02261410 @ 0x02261410, 0x25c bytes, Thumb
 * func_ov049_0226124c @ 0x0226124c, 0x1c4 bytes, Thumb
 * func_ov049_02261224 @ 0x02261224, 0x28 bytes, Thumb
 * func_ov049_022611f8 @ 0x022611f8, 0x2c bytes, Thumb
 * func_ov049_02261160 @ 0x02261160, 0x98 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_022617b4;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x6C];
    void *unk_B0;
} UnkStruct_02261764;

struct UnkStruct_0226171c {
    unsigned char pad_00[0xb0];
    unsigned int unk_B0;
};

typedef struct UnkStruct_02261680 UnkStruct_02261680;

struct UnkStruct_02261680 {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0xb0 - 0x44];
    void *unk_B0;
    unsigned char pad_B4[0xbc - 0xb4];
    void *unk_BC;
    void *unk_C0;
};

typedef struct {
    char pad_00[0x734];
    u16 unk_734;
    u16 unk_736;
    u16 unk_738;
} UnkStruct_02261410;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x6c];
    UnkStruct_02261410 *unk_B0;
    char pad_B4[8];
    int unk_BC;
} UnkStruct_02261410_2;

typedef struct {
    char pad_00[0x734];
    u16 unk_734;
    u16 unk_736;
    u16 unk_738;
} UnkStruct_0226124c;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x6c];
    UnkStruct_0226124c *unk_B0;
    char pad_B4[8];
    int unk_BC;
} UnkStruct_0226124c_2;

typedef struct UnkStruct_02261160 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    void *unk_B0;
} UnkStruct_02261160;

extern void *data_020ccf94;
extern int data_ov049_02263298;
extern int func_02073d90(void *);
extern short *func_0209d358(int, int);
extern int func_02082644(int);
extern void func_020160d8(void *, int);
extern int func_0201b43c(void *a, int b);
extern int func_020644cc(int arg);
extern void func_ov049_02260780(unsigned int a, unsigned int b);
extern unsigned int data_ov049_02262dec[];
extern int func_0201b3c0(void *a, void *b, void *c);
extern void func_0201b3a4(void *a, void *b);
extern void func_0206fa8c(int a);
extern int func_020984e8(void);
extern int func_02099fe8(void);
extern void func_0206844c(int, u8 *, void *);
extern void func_ov049_02260ac4(UnkStruct_02261410_2 *);
extern u16 *func_02099710(int);
extern u16 *func_020996e0(int);
extern u16 *func_020996f8(int);
extern int func_02095b58(u16 *);
extern int func_02095b40(u16 *);
extern void func_02095b4c(u16 *);
extern int func_0204c4c0(u16 *);
extern void func_02095eec(int, int);
extern void func_0203ae98(void);
extern void func_02068440(int);
extern void func_ov049_022610c4(void *, int);
extern int func_0203aeac(void);
extern void func_020157d4(void *obj, unsigned int address, unsigned char state, unsigned char flags);
extern int func_02015828(void *a, int b);
extern int func_0206837c(int h);
extern int func_020ab504(int a);
extern u8 data_ov049_02262dc0[];
extern int func_0202ea40(void *p, u8 *q, int a);
extern void func_0202ea28(void *p, u8 *q);

void func_ov049_022617b4(UnkStruct_022617b4 *p, int type)
{
    void *obj;
    char buf[2];
    int res;

    obj = data_020ccf94;
    if (func_02073d90(obj) != 0 || ((short *) func_0209d358(0, 0x4a))[0] != 0) {
        if (type == 2) {
            buf[0] = 0x1c;
            func_0206844c(p->unk_40, (u8 *) (&buf[0]), (void *) data_ov049_02263298);
        } else if (type == 0) {
            buf[1] = 0x37;
            func_0206844c(p->unk_40, (u8 *) (&buf[1]), (void *) data_ov049_02263298);
        }
    }
    if (func_02073d90(obj) == 0 && ((short *) func_0209d358(0, 0x4a))[0] == 0) {
        res = func_02082644(5);
        if (res != 0) {
            func_020160d8(p, res);
        }
    }
}

void func_ov049_02261764(UnkStruct_02261764 *self, int cond)
{
    char buffer[8];
    if (cond != 0) {
        return;
    }
    if (func_0201b43c(self->unk_B0, 0x15e) == 0) {
        buffer[0] = 0xd;
        func_0206844c((int) self->unk_40, (u8 *) buffer, (void *) data_ov049_02263298);
    } else {
        buffer[1] = 0xe;
        func_0206844c((int) self->unk_40, (u8 *) (&buffer[1]), (void *) data_ov049_02263298);
    }
}

void func_ov049_0226171c(struct UnkStruct_0226171c *param, int idx)
{
    int n = 0;
    switch (idx) {
        case 0:
            n = func_020644cc(3);
            break;
        case 1:
            n = func_020644cc(3) + 3;
            break;
        case 2:
            n = func_020644cc(4) + 6;
            break;
        default:
            break;
    }
    func_ov049_02260780(param->unk_B0, data_ov049_02262dec[n]);
}

void func_ov049_02261680(UnkStruct_02261680 *self, int mode)
{
    char buf[3];

    switch (mode) {
        case 0: {
            int ret = func_0201b3c0(self->unk_B0, self->unk_BC, self->unk_C0);
            switch (ret) {
                case 0:
                    func_0201b3a4(self->unk_B0, self->unk_BC);
                    buf[0] = 0x1a;
                    func_0206844c((int) self->unk_40, (u8 *) (&buf[0]), (void *) ((*(char * *) &data_ov049_02263298)));
                    break;
                case 1:
                    buf[1] = 0x1e;
                    func_0206844c((int) self->unk_40, (u8 *) (&buf[1]), (void *) ((*(char * *) &data_ov049_02263298)));
                    break;
                case 2:
                    buf[2] = 0x38;
                    func_0206844c((int) self->unk_40, (u8 *) (&buf[2]), (void *) ((*(char * *) &data_ov049_02263298)));
                    func_0206fa8c(0);
                    break;
                default:
                    break;
            }
            break;
        }
        case 1:
            func_0206fa8c(0);
            break;
        default:
            break;
    }
}

void func_ov049_0226166c(int r0, int r1)
{
    if (r1 == 1) {
        func_0206fa8c(0);
    }
}

void func_ov049_02261410(UnkStruct_02261410_2 *p, int a1)
{
    struct {
        u8 b[3];
        volatile u16 h4;
        u16 h6;
        u16 h8;
        u16 ha;
        u16 hc;
        u16 he;
    } m;
    int h;

    h = func_020984e8();
    if (a1 == 0) {
        if (func_02099fe8() == -1) {
            m.b[0] = 0x2c;
            func_0206844c(p->unk_40, &m.b[0], (*(void * *) &data_ov049_02263298));
        } else if (func_0201b43c(p->unk_B0, p->unk_BC) == 0) {
            m.b[1] = 0x2b;
            func_0206844c(p->unk_40, &m.b[1], (*(void * *) &data_ov049_02263298));
        } else {
            m.b[2] = 0x29;
            func_0206844c(p->unk_40, &m.b[2], (*(void * *) &data_ov049_02263298));
            func_ov049_02260ac4(p);
        }
    } else if (a1 == 1) {
        unsigned int ok;
        UnkStruct_02261410 *q;
        u16 t;

        p->unk_B0->unk_736 = 0xfff1;
        q = p->unk_B0;
        ok = 0;
        t = q->unk_738;
        if (t >= 0x11a8 && t <= 0x12a7) {
            ok = 1;
        }
        if (ok || (t >= 0x13c8 && t <= 0x1407) || (t >= 0x13a8 && t <= 0x13c7) || (t >= 0x1431 && t <= 0x1470)) {
            if (t >= 0x11a8 && t <= 0x12a7) {
                p->unk_B0->unk_734 = *func_02099710(h);
                m.h6 = p->unk_B0->unk_738;
                func_02095b58(&m.h6);
            } else if ((t >= 0x13c8 && t <= 0x1407) || (t >= 0x13a8 && t <= 0x13c7)) {
                if (t >= 0x13a8 && t <= 0x13c7) {
                    if (func_0204c4c0(&q->unk_738) == 0) {
                        p->unk_B0->unk_736 = *func_020996e0(h);
                        m.h8 = 0xfff1;
                        func_02095b4c(&m.h8);
                    }
                }
                p->unk_B0->unk_734 = *func_020996f8(h);
                m.ha = p->unk_B0->unk_738;
                func_02095b40(&m.ha);
            } else if (t >= 0x1431 && t <= 0x1470) {
                unsigned int ok2;
                u16 a, b;

                p->unk_B0->unk_734 = *func_020996e0(h);
                m.hc = p->unk_B0->unk_738;
                func_02095b4c(&m.hc);
                m.h4 = 0xfff1;
                m.h4 = *func_020996f8(h);
                ok2 = 0;
                a = m.h4;
                b = m.h4;
                if (b >= 0x13a8 && a <= 0x13c7) {
                    ok2 = 1;
                }
                if (ok2) {
                    if (func_0204c4c0((u16 *) &m.h4) == 0) {
                        p->unk_B0->unk_736 = *func_020996f8(h);
                        m.he = 0xfff1;
                        func_02095b40(&m.he);
                    }
                }
            }
            func_02095eec(1, 4);
            func_0203ae98();
            func_02068440(p->unk_40);
            func_ov049_022610c4((void *) p, 7);
        }
    }
}

void func_ov049_0226124c(UnkStruct_0226124c_2 *p, int a1)
{
    struct {
        u8 b[3];
        volatile u16 h4;
        u16 h6;
        u16 h8;
        u16 ha;
        u16 hc;
        u16 he;
    } m;

    {
        unsigned int ok;
        UnkStruct_0226124c *q;
        u16 t;
        q = p->unk_B0;
        ok = 0;
        t = q->unk_738;
        if (t >= 0x11a8 && t <= 0x12a7) {
            ok = 1;
        }
        if (ok) {
            m.h6 = q->unk_734;
            func_02095b58(&m.h6);
        }
    }
    {
        unsigned int ok;
        UnkStruct_0226124c *q;
        u16 t;
        q = p->unk_B0;
        ok = 0;
        t = q->unk_738;
        if (t >= 0x13c8 && t <= 0x1407) {
            ok = 1;
        }
        if (ok || (t >= 0x13a8 && t <= 0x13c7)) {
            m.h8 = q->unk_734;
            func_02095b40(&m.h8);
        }
    }
    {
        unsigned int ok;
        UnkStruct_0226124c *q;
        u16 t;
        q = p->unk_B0;
        ok = 0;
        t = q->unk_738;
        if (t >= 0x1431 && t <= 0x1470) {
            ok = 1;
        }
        if (ok) {
            m.ha = q->unk_734;
            func_02095b4c(&m.ha);
        }
    }
    {
        UnkStruct_0226124c *q;
        q = p->unk_B0;
        if (q->unk_736 != 0xfff1) {
            unsigned int ok;
            u16 a, b;
            m.h4 = q->unk_736;
            ok = 0;
            a = m.h4;
            b = m.h4;
            if (b >= 0x13a8 && a <= 0x13c7) {
                ok = 1;
            }
            if (ok || (a >= 0x13c8 && a <= 0x1407)) {
                m.hc = p->unk_B0->unk_736;
                func_02095b40(&m.hc);
            } else if (a >= 0x1431 && a <= 0x1470) {
                m.he = p->unk_B0->unk_736;
                func_02095b4c(&m.he);
            }
        }
    }

    func_02095eec(0, 4);
    func_ov049_022610c4(p, 8);
    func_0203aeac();
    if (a1 == 0) {
        if (func_02099fe8() == -1) {
            m.b[0] = 0x2c;
            func_0206844c(p->unk_40, &m.b[0], (*(void * *) &data_ov049_02263298));
        } else if (func_0201b43c(p->unk_B0, p->unk_BC) == 0) {
            m.b[1] = 0x2b;
            func_0206844c(p->unk_40, &m.b[1], (*(void * *) &data_ov049_02263298));
        } else {
            m.b[2] = 0x29;
            func_0206844c(p->unk_40, &m.b[2], (*(void * *) &data_ov049_02263298));
            func_ov049_02260ac4((UnkStruct_02261410_2 *) p);
        }
    }
}

unsigned short func_ov049_02261224(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 2) {
        result = 0;
        value = *r0;
        if (value >= 0x155f && value <= 0x1560) {
            result = 1;
        }
        return result;
    }
    return 0;
}

void func_ov049_022611f8(void *param0, int param1)
{
    if (param1 == 0) {
        func_020157d4(param0, (unsigned int) (unsigned short (*)(void *, int)) func_ov049_02261224, 13, 0);
        func_02015828(param0, 0);
        func_ov049_022610c4(param0, 9);
    }
    return;
}

void func_ov049_02261160(UnkStruct_02261160 *self)
{
    u8 m[2];
    int k;
    int v;
    int r;

    v = (int) self->unk_1E;
    if (v >= 0 && v <= 0x11) {
        k = func_020ab504(func_0206837c(self->unk_40));
        if (k != 2) {
            m[1] = data_ov049_02262dc0[k];
            func_0206844c(self->unk_40, &m[1], (void *) data_ov049_02263298);
        } else if (func_0202ea40(self->unk_B0, m, 2) != 0) {
            func_0202ea28(self->unk_B0, m);
        }
    }
    if (func_02073d90((void *) ((*(int *) &data_020ccf94))) == 0 && *func_0209d358(0, 0x4a) == 0 && (r = func_02082644(5)) != 0) {
        func_020160d8((void *) self, r);
    }
}
