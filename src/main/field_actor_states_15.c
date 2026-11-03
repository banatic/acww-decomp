/* field_actor_states_15: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200b3b4 @ 0x0200b3b4, 0x74 bytes, Thumb
 * func_0200b3a8 @ 0x0200b3a8, 0xc bytes, Thumb
 * func_0200b374 @ 0x0200b374, 0x34 bytes, Thumb
 * func_0200b218 @ 0x0200b218, 0x15c bytes, Thumb
 * func_0200ae7c @ 0x0200ae7c, 0x39c bytes, Thumb
 * func_0200ae04 @ 0x0200ae04, 0x78 bytes, Thumb
 * func_0200ad8c @ 0x0200ad8c, 0x78 bytes, Thumb
 * func_0200ad78 @ 0x0200ad78, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0200b218 {
    int x, y, z;
} UnkStruct_0200b218;

typedef struct B48 {
    int w[12];
} B48;

typedef struct Bits {
    u32 b0 : 12;
    u32 b12 : 16;
    u32 b28 : 4;
} Bits;

typedef struct UnkStruct_0200b218_2 {
    int unk_00;
    int unk_04;
} UnkStruct_0200b218_2;

typedef struct UnkStruct_0200b218_3 {
    u8 pad_00[0xc4];
    UnkStruct_0200b218 g;
    short unk_D0;
    u8 pad_D2[0x298 - 0xd2];
    B48 unk_298;
    u8 pad_2C8[0x2d8 - 0x2c8];
    Bits unk_2D8;
    u8 pad_2DC[0x698 - 0x2dc];
    B48 unk_698;
    u8 pad_6C8[0x704 - 0x6c8];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    UnkStruct_0200b218_2 e;
    u8 pad_7DC[0x824 - 0x7dc];
    int unk_824;
    int unk_828;
    int unk_82C;
    int unk_830;
    int unk_834;
    int unk_838;
} UnkStruct_0200b218_3;

typedef struct T12c {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
} T12c;

typedef struct UnkStruct_0200ae7c {
    u8 pad_00[0xec];
    u8 sub_ec[0x10a - 0xec];
    u8 unk_10A;
    u8 pad_10B[0x12c - 0x10b];
    T12c *unk_12C;
    u8 pad_130[0x2d0 - 0x130];
    u8 sub_2d0[0x2e0 - 0x2d0];
    int unk_2E0;
    u8 pad_2E4[0x5a0 - 0x2e4];
    u8 sub_5a0[0x7f0 - 0x5a0];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x810 - 0x804];
    int unk_810;
    u8 pad_814[0x81c - 0x814];
    int unk_81C;
    u16 unk_820;
} UnkStruct_0200ae7c;

typedef struct {
    char pad_00[0x2d0];
    char unk_2D0[0x2d0];
    char unk_5A0[0x164];
    int unk_704;
    char pad_708[0xe8];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0200ae04;

typedef struct {
    unsigned char pad_00[0x7d4];
    unsigned char sub[0x2c];
    unsigned int flags;
} UnkStruct_0200ad8c;

struct In0200ad78 {
    unsigned long x;
    unsigned long y;
};

struct Out0200ad78 {
    unsigned short a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
};

extern void func_0200b794(void *, int *, void *, unsigned short *, unsigned char *);
extern int func_0200b7e8(void *p0, int *p1, int p2, int p3, int p4, short p5);
extern void func_0200f268(int, int);
extern void func_02010f5c(void *s);
extern int func_02056f28(void *ptr, int n);
extern int func_0200f328(void *s, int n);
extern void *func_ov004_0223badc(int);
extern unsigned int *func_0200f27c(UnkStruct_0200b218_3 *s, int k);
extern void func_0200ee40(UnkStruct_0200b218_3 *s);
extern void func_0200f650(UnkStruct_0200b218_3 *s, int a);
extern int data_020d83a4;
extern int data_020d83b4;
extern int func_02056f94(void *p);
extern int func_02096e38(void);
extern int func_0203e1c4(void);
extern void func_020109fc(UnkStruct_0200ae7c *self, int a, int b, int c);
extern int func_0200fbe0(UnkStruct_0200ae7c *self);
extern void func_0205eae0(void *p, int a, int b, int c);
extern void func_0203ee14(UnkStruct_0200ae7c *self, void *b);
extern void func_0203ee08(UnkStruct_0200ae7c *self, void *b);
extern void func_020a8164(void *p, void *g);
extern int func_0203e190(void);
extern int func_0209a110(u16 *p);
extern int func_0206f6d4(int a);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_02043540(int a, int b);
extern int func_0203e19c(void);
extern int func_02008258(UnkStruct_0200ae7c *self, int a);
extern int func_0200d4e8(UnkStruct_0200ae7c *self, int a, int b, int c);
extern unsigned int data_020ccf94;
extern int func_02073908(unsigned int a, unsigned int b);
extern void func_02010d64(void *p);
extern int func_02010ca4(void *p);
extern int func_0200f530(void *p, unsigned int *arr);

void func_0200b3b4(void *self, short arg2)
{
    char *base = (char *) self;
    unsigned char *byte = (unsigned char *) base;
    struct {
        signed char a;
        unsigned char b;
        unsigned short c;
    } st;
    int arr[2];
    int copy[2];

    if (byte[0x8ec] != 0) {
        byte[0x8ec]++;
        return;
    }
    if (*(int *) (base + 0x7f0) != 0) {
        return;
    }

    arr[0] = 0;
    arr[1] = 0;
    func_0200b794(base + 0x8f0, arr, &st, &st.c, &st.b);
    if (st.a >= 0) {
        return;
    }

    copy[0] = arr[0];
    copy[1] = arr[1];
    func_0200b7e8(base, copy, st.c, st.b, 6, arg2);
}

void func_0200b3a8(int p0)
{
    func_0200f268(p0, 13);
}

void func_0200b374(void *s)
{
    func_02010f5c(s);
    if (*(int *) ((char *) s + 0x704) == 22) {
        if (func_02056f28((char *) s + 0x2d0, 9) != 0) {
            func_0200f328(s, 79);
        }
    }
}

void func_0200b218(UnkStruct_0200b218_3 *self)
{
    int tested_value0;
    UnkStruct_0200b218 sv;
    UnkStruct_0200b218 *q;
    B48 a;
    B48 b;
    UnkStruct_0200b218_2 *e;
    int *p;
    u32 v;
    int t;
    short sh;

    if (self->unk_704 != 0x16) {
        self->unk_830 = 0;
        self->unk_834 = 0;
        self->unk_838 = 0;
        func_0200f268((int) self, 0xd);
        return;
    }
    e = &self->e;
    if ((tested_value0 = (int) (e->unk_04)) >= 0) {
        p = func_ov004_0223badc(tested_value0);
        if (p == 0) {
            return;
        }
        self->unk_824 = p[0];
        self->unk_828 = p[1];
        self->unk_82C = p[2];
        func_0200f27c(self, 0xd);
        self->unk_830 = 0x1000;
        self->unk_834 = 0x1000;
        self->unk_838 = 0x1000;
        e->unk_04 = -1;
    }
    v = self->unk_2D8.b12;
    if (v < 6) {
        return;
    }
    t = 0x1000 - (int) ((v - 6) << 12) / 0xc;
    if (t < 0) {
        t = 0;
        func_0200f268((int) self, 0xd);
    }
    self->unk_830 = t;
    self->unk_834 = t;
    self->unk_838 = t;
    q = &self->g;
    sv.x = q->x;
    sv.y = q->y;
    sv.z = q->z;
    sh = self->unk_D0;
    a = self->unk_298;
    b = self->unk_698;
    func_0200ee40(self);
    func_0200f650(self, t);
    self->g.x = *(int *) &sv.x;
    self->g.y = *(int *) &sv.y;
    self->g.z = *(int *) &sv.z;
    self->unk_D0 = sh;
    self->unk_298 = a;
    self->unk_698 = b;
}

void func_0200ae7c(UnkStruct_0200ae7c *self, u8 *state, int cond)
{
    void *b;
    int r;
    int n;
    u16 v[2];

    switch (*state) {
        case 0:
            if (func_02056f94(self->sub_2d0) == 0) {
                break;
            }
            if (self->unk_820 == 0x1520) {
                if (func_02096e38() != 0) {
                    *state = 6;
                    break;
                }
                if (func_0203e1c4() == 0) {
                    break;
                }
                func_020109fc(self, 0x6c, 0, 0);
                r = func_0200fbe0(self);
                if (r == 4) {
                    func_0205eae0(self->sub_5a0, 0, 9, 0);
                } else if (r == 3) {
                    func_0205eae0(self->sub_5a0, 0x13, 3, 0);
                }
                *state = 7;
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee14(self, b);
                func_0200f27c((UnkStruct_0200b218_3 *) self, 0x11);
                func_020a8164((char *) self + 0xec, &data_020d83a4);
                self->unk_10A = 0x12;
                self->unk_12C->unk_08 = 1;
                break;
            }
            if (cond != 0) {
                if (func_0203e190() == 0 && func_0203e1c4() == 0) {
                    break;
                }
                func_020109fc(self, 0x6c, 0, 0);
                r = func_0200fbe0(self);
                if (r == 4) {
                    func_0205eae0(self->sub_5a0, 0, 9, 0);
                } else if (r == 3) {
                    func_0205eae0(self->sub_5a0, 0x13, 3, 0);
                }
                *state = 1;
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee14(self, b);
                func_0200f27c((UnkStruct_0200b218_3 *) self, 0x11);
                func_020a8164((char *) self + 0xec, &data_020d83b4);
                self->unk_10A = 2;
                self->unk_12C->unk_08 = 1;
                break;
            }
            v[1] = self->unk_820;
            func_0209a110(&v[1]);
            *state = 6;
            break;
        case 1:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            *state = 2;
            self->unk_81C = 3;
            break;
        case 2:
            n = self->unk_81C;
            if (n >= 0xf) {
                *state = 3;
            } else {
                if (self->unk_12C == 0) {
                    break;
                }
                if (self->unk_12C->unk_04 != 0) {
                    break;
                }
                if (n == 5) {
                    if (func_0206f6d4(self->unk_820) == 0) {
                        break;
                    }
                    self->unk_81C = 6;
                    break;
                }
                if (n != 6) {
                    break;
                }
                if (func_0206fbc0() == 0) {
                    break;
                }
                self->unk_81C = 0xf;
                self->unk_2E0 = 0x1000;
                if (func_0206fc6c() != 0) {
                    *state = 6;
                    b = self;
                    if (self != 0) {
                        b = (char *) self + 0xec;
                    }
                    func_0203ee08(self, b);
                    func_0200f268((int) self, 0x11);
                    func_0203e19c();
                    break;
                }
                *state = 3;
            }
            // fall through
        case 3:
            if (self->unk_810 != -1) {
                break;
            }
            self->unk_810 = func_02043540(self->unk_800, self->unk_820);
            if (self->unk_810 == -1) {
                break;
            }
            func_020109fc(self, 0, 6, 6);
            *state = 4;
            if (func_0200fbe0(self) == 4) {
                func_0205eae0(self->sub_5a0, 0, 9, 0);
            }
            break;
        case 4:
            if (self->unk_810 != -1) {
                break;
            }
            *state = 5;
            // fall through
        case 5:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268((int) self, 0x11);
            func_0203e19c();
            *state = 6;
            func_020109fc(self, 0, 6, 6);
            if (func_0200fbe0(self) == 4) {
                func_0205eae0(self->sub_5a0, 0, 9, 0);
            }
            break;
        case 6:
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            func_0200f268((int) self, 0xd);
            self->unk_81C = 0xf;
            break;
        case 7:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            *state = 8;
            break;
        case 8:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            *state = 3;
            if (self->unk_810 != -1) {
                break;
            }
            self->unk_810 = func_02043540(self->unk_800, self->unk_820);
            if (self->unk_810 == -1) {
                break;
            }
            *state = 5;
            func_020109fc(self, 0, 6, 6);
            if (func_0200fbe0(self) == 4) {
                func_0205eae0(self->sub_5a0, 0, 9, 0);
            }
            break;
    }
}

void func_0200ae04(UnkStruct_0200ae04 *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        if (self->unk_704 == 0x16 || self->unk_704 == 0x18) {
            func_020109fc((UnkStruct_0200ae7c *) self, 0x6c, 3, 0);
        }
        self->unk_7FC = func_02008258((UnkStruct_0200ae7c *) self, self->unk_7F0);
        func_0200f268((int) self, 0x12);
        func_0200f268((int) self, 0xd);
        if (func_0200fbe0((UnkStruct_0200ae7c *) self) == 4) {
            func_0205eae0(&self->unk_5A0, 0, 9, 0);
        }
    }
}

void func_0200ad8c(UnkStruct_0200ad8c *p)
{
    func_0200b374(p);
    if (func_02073908(data_020ccf94, p->flags)) {
        func_02010d64(p);
        func_02010ca4(p);
        func_0200b218((UnkStruct_0200b218_3 *) p);
        {
            unsigned char *sub = p->sub;
            func_0200ae7c((UnkStruct_0200ae7c *) p, (u8 *) (sub + 8), (unsigned char) (*sub));
        }
    } else {
        unsigned char *sub = (unsigned char *) p + 0x7d4;
        unsigned int arr[2];
        unsigned int v1 = sub[0xa];
        unsigned int v0 = sub[9];
        arr[0] = v0;
        arr[1] = v1;
        func_0200f530(p, arr);
        func_02010d64(p);
        func_0200b218((UnkStruct_0200b218_3 *) p);
        func_0200ae04((UnkStruct_0200ae04 *) p);
    }
}

void func_0200ad78(struct Out0200ad78 *out, const struct In0200ad78 *in, unsigned short a, unsigned char b)
{
    out->b = in->x;
    out->c = in->y;
    out->a = a;
    out->d = b;
}
