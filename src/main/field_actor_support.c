/* field_actor_support: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200eebc @ 0x0200eebc, 0x60 bytes, Thumb
 * func_0200ee40 @ 0x0200ee40, 0x7c bytes, Thumb
 * func_0200ee0c @ 0x0200ee0c, 0x34 bytes, Thumb
 * func_0200edb0 @ 0x0200edb0, 0x5c bytes, Thumb
 * func_0200eda4 @ 0x0200eda4, 0xc bytes, Thumb
 * func_0200ec4c @ 0x0200ec4c, 0x158 bytes, Thumb
 * func_0200ebbc @ 0x0200ebbc, 0x90 bytes, Thumb
 * func_0200ea18 @ 0x0200ea18, 0x1a4 bytes, Thumb
 * func_0200ea0c @ 0x0200ea0c, 0xc bytes, Thumb
 * func_0200e9a8 @ 0x0200e9a8, 0x64 bytes, Thumb
 * func_0200e93c @ 0x0200e93c, 0x6c bytes, Thumb
 * func_0200e92c @ 0x0200e92c, 0x10 bytes, Thumb
 * func_0200e91c @ 0x0200e91c, 0x10 bytes, Thumb
 * func_0200e918 @ 0x0200e918, 0x2 bytes, Thumb
 * func_0200e914 @ 0x0200e914, 0x2 bytes, Thumb
 * func_0200e90c @ 0x0200e90c, 0x8 bytes, Thumb
 */

#include "types.h"

struct LocalType {
    unsigned int data[12];
};

struct UnkStruct_0200ee40 {
    char pad_00[0x5c];
    char unk_5C;
    char pad_5D[0xc4 - 0x5c - 1];
    char unk_C4;
    char pad_C5[0xd0 - 0xc4 - 1];
    unsigned short unk_D0;
    char pad_D2[0x234 - 0xd0 - 2];
    char unk_234;
    char pad_235[0x298 - 0x234 - 1];
    struct LocalType unk_298;
    char _pad5[0x698 - 0x298 - sizeof(struct LocalType)];
    char unk_698;
};

struct UnkStruct_0200ee0c_2 {
    char pad_00[0x800];
    int unk_800;
};

typedef struct UnkStruct_0200ec4c {
    unsigned char pad_00[0x12c];
    int unk_12C;
    unsigned char pad_130[0x7d7 - 0x130];
    u8 unk_7D7;
    unsigned char pad_7D8[0x7dc - 0x7d8];
    u8 unk_7DC;
    unsigned char pad_7DD[0x81c - 0x7dd];
    int unk_81C;
} UnkStruct_0200ec4c;

typedef struct Other {
    unsigned char pad_00[0x248];
    int unk_248;
} Other;

typedef struct Blk {
    int w[0x28 / 4];
} Blk;

struct UnkStruct_0200ea18 {
    u8 pad_00[0x7d4];
    u16 unk_7D4;
    u16 unk_7D6;
    u16 unk_7D8;
    u8 pad_7DA[0x7f0 - 0x7da];
    int unk_7F0;
    u8 pad_7F4[0x81c - 0x7f4];
    int unk_81C;
};

struct UnkStruct_0200e9a8 {
    char pad_00[0x800];
    int value;
};

extern int func_0200fbe0(void *);
extern void func_0205eae0(void *base, int a, int b, int c);
extern struct LocalType data_021cfe68;
extern int func_0203f8d0(void *a, void *b);
extern void func_020031d4(void *a, void *b);
extern void func_02055d38(void *a, int b);
extern void func_02054848(void *a, int b);
extern int func_02055d0c(void *a, void *b, int c);
extern struct UnkStruct_0200ee0c {
    char pad_00[0x64];
    int unk_64;
} *data_020ccf94;
extern int func_02073dd4(struct UnkStruct_0200ee0c *a, int b);
extern int func_020b65b8(void);
extern int func_0209658c(void *, int, int);
extern Other *data_021c526c;
extern void func_0206844c(int h, u8 *p, int k);
extern void *func_02062f90(Blk *out, u16 *src);
extern void func_020683b4(int h, int k, Blk *b, int n);
extern void *func_02062f4c(Blk *b);
extern unsigned int func_0206837c(unsigned int param);
extern unsigned int func_020ab504(void *arg0);
extern unsigned char data_021f43e8;
extern void func_02035638(int a);
extern void func_02035684(int a, int b, int c);
extern void func_020110c4(u16 *out, struct UnkStruct_0200ea18 *self);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0200fc90(struct UnkStruct_0200ea18 *self);
extern u8 data_020e54a8;
extern unsigned char data_020c7ab4[];
extern int func_02096614(void *p1, void *p2, void *p3, int p4, int p5);
extern int FX_MulFunc(int, int);
extern int func_020e8ed8(int, int);

void func_0200e918(void);
void func_0200e914(void);

void func_0200eebc(void *p)
{
    int status;

    status = func_0200fbe0(p);
    if (status == 4) {
        func_0205eae0((char *) p + 0x5a0, 0, 9, 0);
    } else if (status == 3) {
        func_0205eae0((char *) p + 0x5a0, 0x13, 3, 0);
    } else if (status == 0xa) {
        func_0205eae0((char *) p + 0x5a0, 0x23, 3, 0);
    } else if (status == 6) {
        func_0205eae0((char *) p + 0x5a0, 0x21, 3, 0);
    }
}

void func_0200ee40(struct UnkStruct_0200ee40 *self)
{
    struct LocalType local;
    self->unk_D0 = (unsigned short) func_0203f8d0(&self->unk_C4, &self->unk_5C);
    func_020031d4(self, &local);
    self->unk_298 = local;
    data_021cfe68 = self->unk_298;
    func_02055d38(&self->unk_234, 0);
    func_02054848(&self->unk_234, 0);
    func_02055d0c(&self->unk_234, &self->unk_698, 0xb);
}

int func_0200ee0c(struct UnkStruct_0200ee0c_2 *param)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        return 0;
    }
    if (param->unk_800 == 0) {
        return 0;
    }
    return 1;
}

int func_0200edb0(void *self)
{
    int status;
    int i;
    int local;
    unsigned int base;

    status = func_020b65b8();

    if (status == 0xc || status == 0xd || status == 0xe || (unsigned char) (status + 0xd2) <= 1) {
        i = 0;
        base = (*(unsigned int *) &data_020ccf94);
        while (i < 4) {
            if (func_02073dd4((struct UnkStruct_0200ee0c *) base, i) != 0) {
                if (func_0209658c(&local, -1, i) == 0) {
                    return 1;
                }
            }
            i++;
        }
    }

    return 0;
}

void func_0200eda4(int p0)
{
    if (*(int *) ((char *) (p0) + (2076)) == 15) {
        return;
    }
}

void func_0200ec4c(UnkStruct_0200ec4c *self)
{
    struct {
        u8 b[6];
        u16 h6;
        u16 h8;
    } m;
    Blk big1;
    Blk big2;
    int v;

    v = self->unk_81C;
    if (v >= 0xf) {
        return;
    }
    switch (v) {
        case 0:
            m.b[0] = 0x3d;
            func_0206844c(self->unk_12C, &m.b[0], 0);
            break;
        case 4:
            m.b[1] = 0x3e;
            func_0206844c(self->unk_12C, &m.b[1], 0);
            break;
        case 2:
            m.b[2] = 3;
            func_0206844c(self->unk_12C, &m.b[2], 0);
            break;
        case 1:
            m.b[3] = 0x3c;
            func_0206844c(self->unk_12C, &m.b[3], 0);
            self->unk_81C = 9;
            break;
        case 5:
        case 6:
            data_021c526c->unk_248 = 0xb;
            break;
        case 13:
            m.b[4] = 0x3f;
            func_0206844c(self->unk_12C, &m.b[4], 0);
            m.h6 = (u16) (self->unk_7DC + 0x12b0);
            func_02062f90(&big1, &m.h6);
            func_020683b4(self->unk_12C, 0, &big1, 7);
            func_02062f4c(&big1);
            self->unk_81C = 8;
            break;
        case 14:
            m.b[5] = 0x3f;
            func_0206844c(self->unk_12C, &m.b[5], 0);
            self->unk_81C = 8;
            m.h8 = (u16) (self->unk_7D7 + 0x12e8);
            func_02062f90(&big2, &m.h8);
            func_020683b4(self->unk_12C, 0, &big2, 7);
            func_02062f4c(&big2);
            break;
    }
}

void func_0200ebbc(char *a)
{
    int state = *(int *) (a + 0x81c);

    if (state < 0xf) {
        switch (state) {
            case 0:
            case 2:
            case 3:
            case 4: {
                unsigned int ok = func_020ab504((void *) func_0206837c(*(unsigned int *) (a + 0x12c)));
                unsigned char local = data_021f43e8;

                func_0206844c((int) ((void *) (*(int *) (a + 0x12c))), (u8 *) (&local), 0);

                if (ok == 0) {
                    *(int *) (a + 0x81c) = 5;
                } else {
                    switch (*(int *) (a + 0x81c)) {
                        case 0:
                        case 4:
                            *(int *) (a + 0x81c) = 9;
                            break;
                        case 2:
                            *(int *) (a + 0x81c) = 0xb;
                            break;
                        default:
                            *(int *) (a + 0x81c) = 0xf;
                            break;
                    }
                }
                break;
            }
            case 1:
            default:
                break;
        }
    }
}

void func_0200ea18(struct UnkStruct_0200ea18 *self)
{
    u16 w[2];
    int x;
    int st;

    st = self->unk_81C;
    if (st >= 0xf) {
        return;
    }
    x = 6;
    switch (st) {
        case 11:
            x = 0x23;
        case 10:
            func_02035638(0x39);
            func_02035684(0xc, x, x + 5);
            self->unk_81C = 0xf;
            break;
        case 7: {
            u16 v;
            unsigned int ok;
            v = self->unk_7D4;
            func_02035638(v);
            func_020110c4(w, self);
            if (func_0204bcdc(w) != 0) {
                w[1] = 0xfff1;
                if (func_0204bc64(w) == func_0204bc64(&w[1])) {
                    ok = 1;
                } else {
                    ok = 0;
                }
            } else {
                if (w[0] == 0xfff1) {
                    ok = 1;
                } else {
                    ok = 0;
                }
            }
            if (ok == 0) {
                if (func_0200fc90(self) == 0) {
                    unsigned int t;
                    if (data_020e54a8 == 0) {
                        t = 1;
                    } else {
                        t = 0;
                    }
                    if (t != 0) {
                        x += 0x15;
                    }
                }
            }
            if ((u16) (v + 0xffc4) <= 1) {
                func_02035684(5, x, x + 5);
            } else {
                func_02035684(0xc, x, x + 5);
            }
            self->unk_81C = 0xf;
            break;
        }
        case 5:
        case 8: {
            int k;
            int v;
            x = 0xc;
            k = self->unk_7F0;
            if (k == 0x57) {
                v = self->unk_7D8;
                if (v == 0x3b) {
                    x = 5;
                }
            } else if (k == 0x54) {
                v = self->unk_7D4;
                if (v == 0x3a) {
                    x = 5;
                }
            } else if (k == 0x1c) {
                break;
            } else if (k == 0x19) {
                break;
            } else if (k != 0x5f) {
                break;
            } else {
                v = 0x39;
            }
            func_02035638(v);
            func_02035684(x, 0x14, 0x19);
            if (self->unk_81C != 5) {
                self->unk_81C = 0xf;
            }
            break;
        }
        case 9: {
            int v;
            if (self->unk_7F0 == 0x57) {
                v = self->unk_7D8;
                x += 0x1e;
            } else {
                v = self->unk_7D4;
            }
            func_02035638(v);
            func_02035684(0xc, x, x + 5);
            self->unk_81C = 0xf;
            break;
        }
        case 12:
            func_02035638(0x42);
            func_02035684(0xc, x, 0xb);
            self->unk_81C = 0xf;
            break;
    }
}

unsigned char func_0200ea0c(int param1, int index)
{
    return data_020c7ab4[index];
}

int func_0200e9a8(struct UnkStruct_0200e9a8 *a, char *b, int *c, int *d, short *e)
{
    int arg5;
    struct {
        unsigned char byte;
        short word;
        int word1;
        int word2;
    } local;
    int unused;

    arg5 = a->value;
    if (func_02096614(&local.byte, &local.word1, &local.word2, -1, arg5) == 0) {
        return 0;
    }
    if (func_0209658c(&local.word, -1, a->value) == 0) {
        return 0;
    }

    *b = local.byte;
    *c = local.word1;
    *d = local.word2;
    *e = local.word;
    return 1;
}

int func_0200e93c(int a0, int a1, int a2, int a3, short a4, short *a5)
{
    int v, result, diff;

    if (a3 < FX_MulFunc(0x108, 0x108)) {
        return 0;
    }

    v = func_020e8ed8(a1, a2);

    if (a3 >= FX_MulFunc(0x2666, 0x2666)) {
        result = 1;
    } else {
        diff = (short) (v - a4);
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < 0x4000) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result) {
        *a5 = (short) v;
    }

    return result;
}

unsigned int func_0200e92c(unsigned int param)
{
    func_0200e918();
    return param;
}

int func_0200e91c(int arg)
{
    func_0200e914();
    return arg;
}

void func_0200e918(void) {}

void func_0200e914(void) {}

void func_0200e90c(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}
