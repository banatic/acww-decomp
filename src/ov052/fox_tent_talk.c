/* fox_tent_talk: 7 functions, module ov052
 * mwccarm 1.2/base -O4,s
 * func_ov052_022610cc @ 0x022610cc, 0x6 bytes, Thumb
 * func_ov052_022610c4 @ 0x022610c4, 0x6 bytes, Thumb
 * func_ov052_02261054 @ 0x02261054, 0x70 bytes, Thumb
 * func_ov052_02260c1c @ 0x02260c1c, 0x438 bytes, Thumb
 * func_ov052_02260ae0 @ 0x02260ae0, 0x13c bytes, Thumb
 * func_ov052_0226095c @ 0x0226095c, 0x184 bytes, Thumb
 * func_ov052_022608b4 @ 0x022608b4, 0xa8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_022610cc;

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_022610c4;

// Wi-Fi connection screen: a state machine on self->state that fills {text, code}
// from the table at data_ov052_02261be0.

typedef struct {
    u8 pad_00[0xb0];
    int state;  // 0xb0
    u8 *d;      // 0xb4
    int unk_B8; // 0xb8
    int unk_BC; // 0xbc
} UnkStruct_02260c1c;

typedef struct {
    const char *text;
    u8 code;
} UnkStruct_02260c1c_2;

typedef struct {
    const char *text;
    u8 code;
} Entry;

typedef struct UnkStruct_02260ae0 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    char *unk_B4;
    char pad_B8[0xbc - 0xb8];
    int unk_BC;
} UnkStruct_02260ae0;

typedef struct Msg {
    u8 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} Msg;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad_44[0x70];
    int unk_B4;
    int unk_B8;
    int unk_BC;
    u8 unk_C0;
} UnkStruct_0226095c;

typedef struct {
    char pad_00[0xB4];
    unsigned char *ptr;
    unsigned char *other;
} UnkStruct_022608b4;

extern void *func_020adfa4(void *p, unsigned int a, unsigned int b);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern unsigned char data_021f3b30;
extern Entry data_ov052_02261be0[];
extern u16 data_021f3aec;
extern void *data_020ccf94;
extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_02073d90(void *p);
extern int func_02099e9c(u16 *p);
extern int func_0202ea80(int a, int b);
extern u16 *func_02087228(void *record);
extern int func_020951bc(int a);
extern void func_020871cc(u16 *dst, u16 *src);
extern void func_02015de4(UnkStruct_02260c1c *self, u16 *p, int a, int b);
extern int func_02099870(int a);
extern int memcmp(void *a, void *b, int n);
extern int func_0209518c(int a, int b);
extern void func_02015e40(UnkStruct_02260c1c *self, int a, int b);
extern int func_020644cc(int a);
extern int func_0204c878(u16 *p);
extern void func_02015fb0(UnkStruct_02260c1c *self, int a, int b, int c, int d, int e);
extern int func_ov052_02261158(u8 *a, u8 *b, int n);
extern int func_ov052_0226118c(u8 *a, u8 *b, int n);
extern void MI_CpuFill8(u8 *p, int v, int n);
extern int func_020154b4(UnkStruct_02260ae0 *, u16 *, int, int, int);
extern int func_02015330(UnkStruct_02260ae0 *, u16 *, int, int, int);
extern int func_0209a000(u16 *, int);
extern void func_0201b420(char *, int);
extern void func_02098ff8(void *, int);
extern void func_0206844c(void *, u8 *, const void *);
extern int func_020160b4(void *);
extern int func_020ab504(int);
extern int func_0201b43c(int, int);
extern int func_02099fe8(void);
extern void func_0209a050(void *parameter0);
extern char data_ov052_02261e50;
extern void func_020ad890(unsigned int, unsigned int, int);
extern void func_020871dc(void *, int);
extern void func_020871d4(void *, unsigned char *);

void func_ov052_022608b4(UnkStruct_022608b4 *self);

void func_ov052_022610cc(UnkStruct_022610cc *p, unsigned long v)
{
    p->unk_B0 = v;
}

unsigned long func_ov052_022610c4(UnkStruct_022610c4 *p)
{
    return p->unk_B0;
}

int func_ov052_02261054(void *self)
{
    int val, val2;
    unsigned int val3;
    unsigned short local8;
    unsigned int i = 0;
    void *p;
    int t1, t2, cond;

    val = i;
    val3 = i;
    val2 = i;

    while (i < 3) {
        p = func_020adfa4(&data_021f3b30, i, val3);
        if (func_0204bcdc(p) != 0) {
            local8 = 0x1547;
            t1 = func_0204bc64(p);
            t2 = func_0204bc64(&local8);
            cond = (t1 == t2) ? 1 : val;
        } else {
            cond = (*(unsigned short *) p == 0x1547) ? 1 : val2;
        }
        if (cond == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}

void func_ov052_02260c1c(UnkStruct_02260c1c *self, UnkStruct_02260c1c_2 *out)
{
    int t;
    int found;
    int t1, t2;
    int cond;
    int i;
    int k;
    u16 *p;
    u16 *pa;
    u16 *pb;
    int u, v;
    u16 s0, sB, r, sA, sE, sBB, sC;

    t = func_020984e8();

    if (self->state == 12) {
        out->code = data_ov052_02261be0[self->state].code;
        out->text = data_ov052_02261be0[self->state].text;
        return;
    }

    if (self->state != 0 && self->state != 1 && self->state != 2) {
        p = (u16 *) (self->d + 0x71e);
        if (func_0204bcdc((void *) p) != 0) {
            sA = 0xfff1;
            t1 = func_0204bc64((void *) p);
            t2 = func_0204bc64((void *) (&sA));
            cond = (t1 == t2) ? 1 : 0;
        } else {
            cond = (*p == 0xfff1) ? 1 : 0;
        }
        if (cond != 0) {
            if (func_02099020(t, 12) != 0) {
                if (func_02073d90(data_020ccf94) == 0) {
                    if (self->unk_BC == -1) {
                        s0 = 0x34a8;
                        self->unk_BC = func_02099e9c(&s0);
                    }
                }
                if (self->unk_BC >= 0) {
                    self->state = 5;
                } else if (func_ov052_02261054(self) != 0) {
                    self->state = 6;
                } else if (func_0202ea80(1, 1) == 0) {
                    self->state = 7;
                } else {
                    if (func_020951bc((int) func_02087228(&data_021f3aec)) != 0) {
                        func_020871cc(&sB, &data_021f3aec);
                        if (func_0204bcdc((void *) (&sB)) != 0) {
                            sBB = 0xfff1;
                            t1 = func_0204bc64((void *) (&sB));
                            t2 = func_0204bc64((void *) (&sBB));
                            cond = (t1 == t2) ? 1 : 0;
                        } else {
                            cond = (sB == 0xfff1) ? 1 : 0;
                        }
                        if (cond == 0) {
                            func_020871cc(&r, &data_021f3aec);
                            func_02015de4(self, &r, 0, 7);
                            v = func_02099870(func_020984e8());
                            u = (int) func_02087228(&data_021f3aec);
                            if (*(u16 *) u != *(u16 *) v || memcmp((void *) (u + 2), (void *) (v + 2), 12) != 0 ||
                                func_0209518c(u, v) == 0) {
                                func_02015e40(self, (int) func_02087228(&data_021f3aec), 1);
                                self->state = 8;
                            } else {
                                func_02015e40(self, func_02099870(t), 1);
                                self->state = 9;
                            }
                            goto Ldfe;
                        }
                    }
                    self->state = 10;
                }
            }
        }
    }

Ldfe:
    if (self->state >= 0 && self->state < 13) {
        out->code = data_ov052_02261be0[self->state].code;
        if (func_02099020(t, 12) != 0) {
            if (self->state == 10) {
                out->code = (u8) (func_020644cc(4) + 0x17);
                if (out->code == 0x1a) {
                    out->code = 0x30;
                }
            }
            found = 0;
            p = (u16 *) (self->d + 0x71e);
            if (func_0204bcdc((void *) p) != 0) {
                sC = 0xfff1;
                t1 = func_0204bc64((void *) p);
                t2 = func_0204bc64((void *) (&sC));
                cond = (t1 == t2) ? 1 : 0;
            } else {
                cond = (*p == 0xfff1) ? 1 : 0;
            }
            if (cond == 0) {
                self->unk_B8 = func_0204c878((u16 *) (self->d + 0x71e)) * 2;
                func_02015de4(self, (u16 *) (self->d + 0x71e), 1, 7);
                func_02015fb0(self, self->unk_B8, 2, 10, 0, 0);
                for (i = 0; i < 3; i++) {
                    pb = (u16 *) (self->d + 0x720 + i * 2);
                    pa = (u16 *) (self->d + 0x71e);
                    if (func_0204bcdc((void *) pa) != 0) {
                        t1 = func_0204bc64((void *) pa);
                        t2 = func_0204bc64((void *) pb);
                        cond = (t1 == t2) ? 1 : 0;
                    } else {
                        cond = (*pa == *pb) ? 1 : 0;
                    }
                    if (cond != 0) {
                        out->code = 0x1d;
                        goto Lafter;
                    }
                    pb = (u16 *) (self->d + 0x720 + i * 2);
                    if (func_0204bcdc((void *) pb) != 0) {
                        sE = 0xfff1;
                        t1 = func_0204bc64((void *) pb);
                        t2 = func_0204bc64((void *) (&sE));
                        cond = (t1 == t2) ? 1 : 0;
                    } else {
                        cond = (*pb == 0xfff1) ? 1 : 0;
                    }
                    if (cond != 0) {
                        found = i;
                    }
                }
            Lafter:
                if (out->code != 0x1d) {
                    k = func_ov052_02261158(self->d, self->d + 0x733, 5);
                    if ((self->d + 0x733)[k] == 0) {
                        (self->d + 0x733)[k] = 1;
                        *(u16 *) (self->d + found * 2 + 0x720) = *(u16 *) (self->d + 0x71e);
                    }
                    if (func_ov052_0226118c(self->d, self->d + 0x733, 5) == 0) {
                        MI_CpuFill8(self->d + 0x733, 0, 5);
                        (self->d + 0x733)[k] = 1;
                        *(u16 *) (self->d + found * 2 + 0x720) = *(u16 *) (self->d + 0x71e);
                    }
                    out->code = (u8) (k + 0x1e);
                }
            }
        }
        out->text = data_ov052_02261be0[self->state].text;
    }
}

void func_ov052_02260ae0(UnkStruct_02260ae0 *this)
{
    Msg m;
    const void *tag = (const void *) ((const int *) &data_ov052_02261e50);
    int code = 0xff;
    void *a = (void *) func_020984e8();
    int st = this->unk_1E;

    switch (st) {
        case 0x2e:
            m.unk_02 = 0x36fc;
            func_020154b4(this, &m.unk_02, 0, 5, 0);
            m.unk_04 = 0x36fc;
            func_0209a000(&m.unk_04, 0);
            code = 0x2f;
            // fallthrough
        case 0x2d:
            this->unk_BC = ~1;
            break;
        case 6:
            if (func_02099020((int) a, 0xc) == 0) {
                func_ov052_022610cc((UnkStruct_022610cc *) this, 3);
            } else {
                func_ov052_022610cc((UnkStruct_022610cc *) this, 0xa);
            }
            break;
        case 7:
            func_ov052_022610cc((UnkStruct_022610cc *) this, 4);
            break;
        case 0x10:
            m.unk_06 = 0x149d;
            func_02015330(this, &m.unk_06, 0, 5, 0);
            *(u16 *) (this->unk_B4 + 0x71e) = 0xfff1;
            code = 0x11;
            func_0201b420(this->unk_B4, 0xbb8);
            func_ov052_022610cc((UnkStruct_022610cc *) this, 7);
            func_02098ff8(a, 0xc);
            func_0202ea80(1, 1);
            break;
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
            func_ov052_022608b4((UnkStruct_022608b4 *) this);
            break;
    }
    if (code != 0xff) {
        m.unk_00 = (u8) code;
        func_0206844c(this->unk_40, &m.unk_00, tag);
    }
}

void func_ov052_0226095c(UnkStruct_0226095c *p)
{
    struct {
        u8 b;
        u16 h;
    } m;
    int r;
    void *dp;
    int code;
    int v;

    r = func_020ab504(func_020160b4(p));
    dp = &data_ov052_02261e50;
    code = 0xff;
    v = p->unk_1E;
    switch (v) {
        case 0x2c:
            if (r == 0) {
                if (p->unk_BC >= 0) {
                    func_0209a050((void *) (*(
                        int *) ((char *) (((unsigned int) (((unsigned int) (((unsigned int) (p) + (0x0))) + (0x0))) +
                                           (0xbc))) +
                                0)));
                    m.h = 0x34a8;
                    func_02015330((UnkStruct_02260ae0 *) p, &m.h, 0, 5, 0);
                }
                code = 0x2e;
            }
            break;
        case 7:
        case 0x12:
            if (r != 0) {
                if (func_0201b43c(p->unk_B4, 0xbb8) == 0) {
                    code = 0xa;
                } else if (p->unk_C0 == 0) {
                    code = 8;
                } else {
                    code = 0xc;
                }
            }
            break;
        case 9:
            p->unk_C0 = 1;
            if (r == 0) {
                code = 0xc;
            }
            break;
        case 0x1d:
        case 0x1e:
        case 0x1f:
        case 0x20:
        case 0x21:
        case 0x22:
            if (r == 0) {
                if (func_0201b43c(p->unk_B4, p->unk_B8) != 0) {
                    if (func_02099fe8() >= 0) {
                        int idx = func_ov052_02261158((u8 *) p->unk_B4, (u8 *) (p->unk_B4 + 0x738), 5);
                        *(u8 *) (p->unk_B4 + idx + 0x738) = 1;
                        if (func_ov052_0226118c((u8 *) p->unk_B4, (u8 *) (p->unk_B4 + 0x738), 5) == 0) {
                            MI_CpuFill8((u8 *) ((void *) (p->unk_B4 + 0x738)), 0, 5);
                            *(u8 *) (p->unk_B4 + idx + 0x738) = 1;
                        }
                        code = (u8) (idx + 0x24);
                        break;
                    }
                    code = 0x2a;
                } else {
                    code = 0x29;
                }
            }
            *(u16 *) (p->unk_B4 + 0x71e) = 0xfff1;
            break;
    }

    if (code != 0xff) {
        m.b = (u8) code;
        func_0206844c((void *) p->unk_40, &m.b, (const void *) dp);
    }
}

void func_ov052_022608b4(UnkStruct_022608b4 *self)
{
    func_0201b420((char *) self->ptr, (int) self->other);
    func_0209a000((u16 *) (self->ptr + 0x71e), 0);
    func_020ad890(*(unsigned int *) (self->ptr + 0x728), *(unsigned int *) (self->ptr + 0x72c), 0xf);

    {
        void *p = (void *) ((int *) &data_021f3aec);
        int ret;
        ret = func_02099870((int) func_020984e8());
        func_020871dc(p, ret);
        func_020871d4(p, self->ptr + 0x71e);
    }

    func_02015fb0((UnkStruct_02260c1c *) self, (int) self->other, 2, 10, 0, 0);
    *(unsigned short *) (self->ptr + 0x71e) = 0xfff1;
    *(unsigned char *) (self->ptr + 0x732) = 1;
}
