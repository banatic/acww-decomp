/* chat_scene_3: 34 functions, module ov111
 * mwccarm 1.2/base -O4,s
 * func_ov111_0229fcb0 @ 0x0229fcb0, 0x58 bytes, Thumb
 * func_ov111_0229fc9c @ 0x0229fc9c, 0x14 bytes, Thumb
 * func_ov111_0229fc38 @ 0x0229fc38, 0x64 bytes, Thumb
 * func_ov111_0229fb8c @ 0x0229fb8c, 0xac bytes, Thumb
 * func_ov111_0229fb48 @ 0x0229fb48, 0x44 bytes, Thumb
 * func_ov111_0229faf4 @ 0x0229faf4, 0x54 bytes, Thumb
 * func_ov111_0229facc @ 0x0229facc, 0x26 bytes, Thumb
 * func_ov111_0229fa78 @ 0x0229fa78, 0x54 bytes, Thumb
 * func_ov111_0229fa50 @ 0x0229fa50, 0x26 bytes, Thumb
 * func_ov111_0229f9fc @ 0x0229f9fc, 0x54 bytes, Thumb
 * func_ov111_0229f9d4 @ 0x0229f9d4, 0x26 bytes, Thumb
 * func_ov111_0229f994 @ 0x0229f994, 0x40 bytes, Thumb
 * func_ov111_0229f92c @ 0x0229f92c, 0x68 bytes, Thumb
 * func_ov111_0229f860 @ 0x0229f860, 0xcc bytes, Thumb
 * func_ov111_0229f854 @ 0x0229f854, 0xc bytes, Thumb
 * func_ov111_0229f730 @ 0x0229f730, 0x124 bytes, Thumb
 * func_ov111_0229f6d4 @ 0x0229f6d4, 0x5c bytes, Thumb
 * func_ov111_0229f6a8 @ 0x0229f6a8, 0x2c bytes, Thumb
 * func_ov111_0229f660 @ 0x0229f660, 0x48 bytes, Thumb
 * func_ov111_0229f600 @ 0x0229f600, 0x60 bytes, Thumb
 * func_ov111_0229f5bc @ 0x0229f5bc, 0x44 bytes, Thumb
 * func_ov111_0229f598 @ 0x0229f598, 0x24 bytes, Thumb
 * func_ov111_0229f554 @ 0x0229f554, 0x44 bytes, Thumb
 * func_ov111_0229f524 @ 0x0229f524, 0x30 bytes, Thumb
 * func_ov111_0229f504 @ 0x0229f504, 0x20 bytes, Thumb
 * func_ov111_0229f4dc @ 0x0229f4dc, 0x28 bytes, Thumb
 * func_ov111_0229f4c4 @ 0x0229f4c4, 0x18 bytes, Thumb
 * func_ov111_0229f430 @ 0x0229f430, 0x94 bytes, Thumb
 * func_ov111_0229f3ac @ 0x0229f3ac, 0x84 bytes, Thumb
 * func_ov111_0229f358 @ 0x0229f358, 0x54 bytes, Thumb
 * func_ov111_0229f2ec @ 0x0229f2ec, 0x6c bytes, Thumb
 * func_ov111_0229f288 @ 0x0229f288, 0x64 bytes, Thumb
 * func_ov111_0229f24c @ 0x0229f24c, 0x3c bytes, Thumb
 * func_ov111_0229f1fc @ 0x0229f1fc, 0x50 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    unsigned int unk_64;
} GStruct;

struct UnkStruct_0229fc9c {
    char unk_00[0x64];
    unsigned int unk_64;
};

typedef struct {
    char pad_00[0x9e];
    char unk_9E;
    char pad_9F[0x0d];
    char unk_AC;
    char pad_AD[0x3c69];
    char unk_3D16;
} UnkStruct_0229fc38;

typedef struct {
    u8 pad_00[0x9e];
    u8 unk_9E;
    u8 unk_9F;
    u8 unk_A0;
    u8 pad_A1[0xac - 0xa1];
    u8 unk_AC;
    u8 pad_AD[0x3d16 - 0xad];
    u16 unk_3D16;
} UnkStruct_0229fb8c;

typedef struct UnkStruct_0229f860 {
    u8 pad_00[0x9e];
    u8 unk_9E;
    u8 unk_9F;
    u8 unk_A0;
    u8 pad_A1[0xac - 0xa1];
    u8 pad_AC[0x3eb8 - 0xac];
    u16 arr_3eb8[1];
} UnkStruct_0229f860;

struct UnkStruct_0229f730 {
    char pad_00[0xa2];
    u8 unk_A2;
    char pad_A3[0xac - 0xa3];
    char unk_AC[1];
};

struct UnkStruct_0229f600 {
    char pad_00[0x9e];
    unsigned char unk_9E;
    unsigned char unk_9F;
    unsigned char unk_A0;
};

struct UnkStruct_0229f5bc {
    char pad_00[0x9e];
    unsigned char unk_9E;
    unsigned char pad_9F;
    unsigned char unk_A0;
};

struct UnkStruct_0229f598 {
    unsigned char pad_00[0xa1];
    char unk_A1;
    unsigned char pad_A2[0xac - 0xa1 - 1];
    char unk_AC;
};

typedef struct UnkStruct_0229f524 {
    unsigned char pad_00[0x9C];
    unsigned char unk_9C;
    unsigned char pad_9D[1];
    unsigned char unk_9E;
    unsigned char pad_9F[2];
    unsigned char unk_A1;
    unsigned char pad_A2[0x3C74];
    unsigned char big_field;
} UnkStruct_0229f524;

typedef struct {
    unsigned char pad_00[0x9e];
    unsigned char unk_9E;
} UnkStruct_0229f430;

typedef struct UnkStruct_0229f358 {
    unsigned char unk_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x0a];
    unsigned char unk_98;
    unsigned char pad_99[0x13];
    void *unk_AC;
} UnkStruct_0229f358;

struct UnkStruct_0229f288 {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x98 - 0x8d - 1];
    unsigned char unk_98;
    char pad_99[0xac - 0x98 - 1];
    unsigned char unk_AC;
};

struct UnkStruct_0229f288_2 {
    char pad_00[2];
    unsigned short unk_02;
};

typedef struct Struct_ov111_0229f1fc {
    char pad_00[0xac];
    int unk_AC;
    char pad_B0[0x3d38 - 0xac - 4];
    int unk_3D38;
} Struct_ov111_0229f1fc;

extern GStruct *data_020ccf94;
extern unsigned int func_020984e8(void);
extern void *func_02094fd4(unsigned char *buf);
extern unsigned int func_02099870(unsigned int v);
extern void *func_02095074(unsigned int a, unsigned char *buf);
extern int func_020b4424(unsigned char *p);
extern void func_020398e8(unsigned int a, unsigned char *b, unsigned char *c);
extern void *func_02094fbc(unsigned char *buf);
extern void func_020398d4(unsigned int);
extern void func_ov095_0229b3ec(void *p);
extern int func_ov095_0229bcec(void *a, void *b, int c, void *d, int e, int f, int g, int h);
extern int func_ov095_0229b3a0(void *ptr, void *ptr2, int _x);
extern void func_0200467c(int cmd);
extern void func_ov111_0229fd08(void *self);
extern unsigned char func_ov095_0229bbc0(void *a, void *b, unsigned char c, unsigned char d, int e);
extern int func_ov095_0229bb9c(void *receiver, int value);
extern int func_ov095_0229bba0(void *a, unsigned short *b, int c, int d);
extern int func_ov095_0229bb98(void *receiver, int value);
extern int func_ov095_0229bb94(void *receiver, int value);
extern void func_ov111_0229efec(void *);
extern void func_02051bf8(void *, int);
extern void func_ov095_0229cd30(void *);
extern void func_02051c08(void *, const void *, int);
extern void func_ov111_0229efc8(void *, int);
extern void func_ov095_022999f4(void *receiver);
extern int func_ov111_0229efd8(UnkStruct_0229f860 *s, int v);
extern void func_ov095_0229b394(void *p);
extern int func_02051c8c_unk(u16 *arr, int size);
extern void func_ov095_022999e8(void *receiver);
extern void func_ov095_0229b388(void *p);
extern int func_ov095_0229ba44(void *p, int param, int six);
extern int func_ov095_0229bebc(void *p, int param);
extern int func_ov111_022a09f8(void *self, int a, int b);
extern int func_ov095_0229af98(void *p, int param);
extern void func_ov111_022a0198(void *self);
extern void func_ov111_0229f0cc(void *self);
extern void func_ov095_0229cce0(void *self);
extern int func_ov095_0229c54c(void *self, unsigned char a, unsigned char b);
extern int func_ov095_0229c448(void *self, int a, int b);
extern void func_ov095_0229c8e4(void *self, int a);
extern void func_ov095_0229bf3c(void *self);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov095_0229b058(void *p);
extern int func_02095804(void);
extern int func_ov095_0229bb34(void *dst, const void *src, int width, int height, unsigned char flag, void *ptr);
extern unsigned char func_02051d08(void *ptr, unsigned char byte);
extern void func_ov111_0229efb8(void *p, int a);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern unsigned short data_021fbe40[2];
extern int func_ov095_02299a00(void *ptr);
extern void func_ov002_0220a1dc(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov111_0229f0ec(void *ptr);
extern int func_ov095_0229cf64(void *ptr, int num);
extern void func_ov111_0229f10c(void *ptr);
extern void func_ov111_0229f1d8(void *p);
extern void func_ov095_02299aec(void *p);
extern int func_ov095_02299b7c(void *p);
extern int func_ov095_02299b38(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov111_0229f0a4(void *p);

void func_ov111_0229fb48(unsigned char *self);
void func_ov111_0229f994(void *self);
void func_ov111_0229f854(void *receiver);
int func_ov111_0229f660(unsigned char *self);
void func_ov111_0229f598(struct UnkStruct_0229f598 *self, int value);
void func_ov111_0229f554(void *param);
void func_ov111_0229f524(UnkStruct_0229f524 *self);
unsigned short func_ov111_0229f504(unsigned char *s);
int func_ov111_0229f4dc(unsigned char *p);
void func_ov111_0229f4c4(void *p);

void func_ov111_0229fcb0(unsigned char *self)
{
    unsigned char buf[0x24];
    unsigned int v = func_020984e8();

    func_02094fd4(buf);
    func_02095074(func_02099870(v), buf);
    func_020b4424(self + 0x3cd4);
    func_020398e8(data_020ccf94->unk_64, buf, self + 0x3cd4);
    func_ov111_0229f994((void *) self);
    func_ov111_0229fd08((void *) self);
    func_02094fbc(buf);
}

void func_ov111_0229fc9c(void *receiver)
{
    func_020398d4((*(struct UnkStruct_0229fc9c * *) &data_020ccf94)->unk_64);
}

int func_ov111_0229fc38(UnkStruct_0229fc38 *self, int param)
{
    if (func_ov111_0229f4dc((unsigned char *) self)) {
        func_ov111_0229fb48((unsigned char *) self);
        func_ov095_0229b3ec(&self->unk_AC);
    }
    if (func_ov095_0229bcec(&self->unk_AC, &self->unk_3D16, param, &self->unk_9E, 0x10, 0xa0, 0, 1)) {
        func_ov111_0229f524((UnkStruct_0229f524 *) self);
        func_ov111_0229fd08((void *) self);
    } else {
        return 0;
    }
    return 1;
}

int func_ov111_0229fb8c(UnkStruct_0229fb8c *self, int param1)
{
    if (func_ov111_0229f4dc((unsigned char *) self) != 0) {
        func_ov095_0229b3ec(&self->unk_AC);
        func_ov111_0229fb48((unsigned char *) self);
    } else {
        if (self->unk_9E != 0) {
            if (func_ov095_0229b3a0(&self->unk_AC, (u8 *) self + 0x3d16, self->unk_9E) == 0) {
                self->unk_9F = self->unk_9E;
                self->unk_A0 = self->unk_9E - 1;
                func_ov111_0229fb48((unsigned char *) self);
            }
        } else {
            if (self->unk_3D16 != 0) {
                self->unk_9F = 0;
                self->unk_A0 = 1;
                func_ov111_0229fb48((unsigned char *) self);
            } else {
                if (param1 != 0) {
                    func_0200467c(0x34);
                }
                return 0;
            }
        }
    }
    func_0200467c(0x35);
    func_ov111_0229fd08(self);
    func_ov111_0229f524((UnkStruct_0229f524 *) self);
    return 1;
}

void func_ov111_0229fb48(unsigned char *self)
{
    unsigned char x = self[0xA0];
    unsigned char y = self[0x9F];
    unsigned char min, max;

    if (y > x) {
        min = x;
        max = y;
    } else {
        min = y;
        max = x;
    }

    self[0x9E] = func_ov095_0229bbc0(self + 0xAC, self + 0x3D16, min, max, 16);
    func_ov111_0229f4c4(self);
}

int func_ov111_0229faf4(void *s)
{
    volatile int argument_values[2];
    int v;
    int x;
    unsigned char idx;

    v = func_ov111_0229f504((unsigned char *) s);
    if (v == 0) {
        return 0;
    }
    x = func_ov095_0229bb9c((char *) s + 0xac, v);
    if (x == 0) {
        return 0;
    }
    idx = *((unsigned char *) s + 0x9e);
    return (argument_values[0] = (int) (0x10), argument_values[1] = (int) (0xa0),
            func_ov095_0229bba0((char *) s + 0xac, (unsigned short *) ((char *) s + 0x3d16), x, idx)) != 0;
}

void func_ov111_0229facc(void *value_r0)
{
    void *value_r4 = value_r0;
    if (func_ov111_0229faf4(value_r4) != 0) {
        func_ov111_0229f524((UnkStruct_0229f524 *) value_r4);
        func_ov111_0229fd08(value_r4);
    } else {
        func_ov111_0229f854((void *) value_r4);
    }
}

int func_ov111_0229fa78(void *s)
{
    volatile int argument_values[2];
    int v;
    int x;
    unsigned char idx;

    v = func_ov111_0229f504((unsigned char *) s);
    if (v == 0) {
        return 0;
    }
    x = func_ov095_0229bb98((char *) s + 0xac, v);
    if (x == 0) {
        return 0;
    }
    idx = *((unsigned char *) s + 0x9e);
    return (argument_values[0] = (int) (0x10), argument_values[1] = (int) (0xa0),
            func_ov095_0229bba0((char *) s + 0xac, (unsigned short *) ((char *) s + 0x3d16), x, idx)) != 0;
}

void func_ov111_0229fa50(int param)
{
    if (func_ov111_0229fa78((void *) param)) {
        func_ov111_0229f524((UnkStruct_0229f524 *) param);
        func_ov111_0229fd08((void *) param);
    } else {
        func_ov111_0229f854((void *) param);
    }
}

int func_ov111_0229f9fc(void *s)
{
    volatile int argument_values[2];
    int v;
    int x;
    unsigned char idx;

    v = func_ov111_0229f504((unsigned char *) s);
    if (v == 0) {
        return 0;
    }
    x = func_ov095_0229bb94((char *) s + 0xac, v);
    if (x == 0) {
        return 0;
    }
    idx = *((unsigned char *) s + 0x9e);
    return (argument_values[0] = (int) (0x10), argument_values[1] = (int) (0xa0),
            func_ov095_0229bba0((char *) s + 0xac, (unsigned short *) ((char *) s + 0x3d16), x, idx)) != 0;
}

void func_ov111_0229f9d4(int value_r0)
{
    int value_r4 = value_r0;
    if (func_ov111_0229f9fc((void *) value_r0) != 0) {
        func_ov111_0229f524((UnkStruct_0229f524 *) value_r4);
        func_ov111_0229fd08((void *) value_r4);
    } else {
        func_ov111_0229f854((void *) value_r4);
    }
}

void func_ov111_0229f994(void *self)
{
    char *p;
    char *q;
    char *r;
    char *s;

    p = (char *) self + 0x9c;
    *p = 0x10;
    q = (char *) self + 0xa1;
    *q = 0;
    r = (char *) self + 0x9e;
    *r = 0;
    func_ov111_0229f4c4(self);
    func_ov111_0229efec(self);
    s = (char *) self + 0xac;
    func_ov095_0229cd30(s);
    func_02051bf8((char *) self + 0x3d16, 0x10);
}

void func_ov111_0229f92c(char *p)
{
    if (func_ov111_0229f4dc((unsigned char *) p)) {
        unsigned char b = p[0xa0];
        unsigned char a = p[0x9f];
        int x, y;
        if (a > b) {
            x = b;
            y = a - b;
        } else {
            x = a;
            y = b - a;
        }
        func_02051bf8(p + 0x3eb8, 0x10);
        func_02051c08(p + 0x3d16 + 2 * x, p + 0x3eb8, y);
        func_ov111_0229efc8(p, 8);
        func_ov095_022999f4(p + 0xac);
        func_ov111_0229efec(p);
    }
}

void func_ov111_0229f860(UnkStruct_0229f860 *s)
{
    int n;
    int i;
    int z;

    if (func_ov111_0229efd8(s, 8) == 0) {
        return;
    }

    func_ov095_0229b394((char *) s + 0xac);

    if (func_ov111_0229f4dc((unsigned char *) s) != 0) {
        s->unk_9E = (u8) func_ov095_0229bbc0((char *) s + 0xac, (char *) s + 0x3d16, (u8) s->unk_9F, (u8) s->unk_A0, 0x10);
        func_ov111_0229efb8((void *) s, 1);
    }

    func_ov095_0229b3ec((char *) s + 0xac);

    n = func_02051c8c_unk(s->arr_3eb8, 0x10);
    i = 0;
    z = i;

    while (i < n) {
        if (func_ov095_0229bcec((char *) s + 0xac, (char *) s + 0x3d16, (u16) s->arr_3eb8[i], &s->unk_9E, 0x10, 0xa0, z, z) == 0) {
            if (i == 0) {
                func_ov111_0229f854((void *) s);
            }
            i = n;
        }
        i++;
    }

    func_ov111_0229f524((UnkStruct_0229f524 *) s);
    func_ov111_0229fd08((void *) s);
    func_ov095_022999e8((char *) s + 0xac);
    s = (UnkStruct_0229f860 *) ((char *) s + 0xac);
    func_ov095_0229b388(s);
}

void func_ov111_0229f854(void *receiver)
{
    func_0200467c(0x34);
}

int func_ov111_0229f730(struct UnkStruct_0229f730 *self, int param)
{
    int ret = 1;
    int res = func_ov095_0229ba44(self->unk_AC, param, 6);

    if (res != 0) {
        func_ov111_0229fd08(self);
        return res;
    }

    if (func_ov095_0229bebc(self->unk_AC, param) != 0) {
        switch (param - 0x100) {
            case 0:
                func_ov111_0229fb8c((UnkStruct_0229fb8c *) self, ret);
                break;
            case 3:
                func_ov111_0229facc(self);
                ret = 2;
                break;
            case 4:
                func_ov111_0229fa50((int) self);
                ret = 2;
                break;
            case 5:
                func_ov111_0229f9d4((int) self);
                ret = 2;
                break;
            case 24:
                func_ov111_0229f92c((char *) self);
                ret = 2;
                break;
            case 25:
                func_ov111_0229f860((UnkStruct_0229f860 *) self);
                ret = 2;
                break;
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                func_ov111_022a09f8(self, param - 0x10a, 0);
                ret = 2;
                break;
            case 27:
            case 28:
            case 29:
            case 30:
                if (self->unk_A2 != 0) {
                    return 0;
                }
                func_ov095_0229af98(self->unk_AC, param);
                func_ov111_022a0198(self);
                func_ov111_0229f0cc(self);
                ret = 3;
                break;
            case 6:
                break;
            default:
                return 0;
        }
    } else {
        if (func_ov111_0229fc38((UnkStruct_0229fc38 *) self, (u16) ((u16) param)) == 0) {
            func_ov111_0229f854(self);
        }
    }

    return ret;
}

int func_ov111_0229f6d4(void *self)
{
    int r4, r6;
    void *p;

    p = (char *) self + 0xac;
    func_ov095_0229cce0(p);

    r4 = func_ov095_0229c54c((char *) self + 0xac, data_021f6c58, data_021f6c54);

    if (r4 != -1) {
        r6 = func_ov111_0229f730((struct UnkStruct_0229f730 *) self, func_ov095_0229c448((char *) self + 0xac, r4, 9));
        func_ov095_0229c8e4((char *) self + 0xac, r4);
        func_ov095_0229bf3c((char *) self + 0xac);
        return r6;
    }
    return 0;
}

int func_ov111_0229f6a8(void *self)
{
    if (*(unsigned char *) ((char *) self + 0x9b) != 0) {
        return 0;
    }
    if (func_ov095_0229b058((char *) self + 0xac) != 0) {
        return func_ov111_0229f660((unsigned char *) self);
    }
    return 0;
}

int func_ov111_0229f660(unsigned char *self)
{
    if (self[0x9b]) {
        return 0;
    }
    if (func_02051c8c_unk((u16 *) (self + 0x3d16), 0x10) == 0) {
        func_ov111_0229f854((void *) self);
    } else {
        func_02095804();
        func_0200467c(0x32);
        func_ov111_0229fc9c((void *) self);
        return 1;
    }
    return 0;
}

int func_ov111_0229f600(struct UnkStruct_0229f600 *self)
{
    int g1 = data_021f6c58;
    int g2 = data_021f6c54;
    int clamp;

    if (g2 < 0x24 || g2 >= 0x3c) {
        return 0;
    }
    if (g1 < 0x10 || g1 >= 0xc8) {
        return 0;
    }
    clamp = g1;
    if (clamp < 0x18) {
        clamp = 0x18;
    }
    func_ov111_0229f598((struct UnkStruct_0229f598 *) self, clamp);
    func_ov111_0229efc8((void *) self, 1);
    self->unk_9F = self->unk_9E;
    self->unk_A0 = self->unk_9E;
    return 1;
}

void func_ov111_0229f5bc(struct UnkStruct_0229f5bc *self)
{
    int val;
    val = data_021f6c58;
    if (val < 0x18) {
        val = 0x18;
    }
    if (val >= 0xc8) {
        val = 0xc7;
    }
    func_ov111_0229f598((struct UnkStruct_0229f598 *) self, val);
    if (self->unk_A0 != self->unk_9E) {
        func_0200467c(0x15);
    }
    self->unk_A0 = self->unk_9E;
}

void func_ov111_0229f598(struct UnkStruct_0229f598 *self, int value)
{
    int new_val = value - 0x18;
    self->unk_A1 = new_val;
    func_ov111_0229f554(self);
    func_ov095_0229b3ec(&self->unk_AC);
    func_ov111_0229fd08(self);
}

void func_ov111_0229f554(void *param)
{
    unsigned char old_a1;
    void *ptr_9e;
    old_a1 = *(unsigned char *) ((char *) param + 0xa1);
    ptr_9e = (char *) param + 0x9e;
    *(unsigned char *) ((char *) param + 0xa1) =
        (unsigned char) func_ov095_0229bb34((char *) param + 0xac, (char *) param + 0x3d16, 0x10, 0xa0, old_a1, ptr_9e);
    *(unsigned char *) ((char *) param + 0x9c) = 0x10;
    func_ov111_0229efec(param);
}

void func_ov111_0229f524(UnkStruct_0229f524 *self)
{
    unsigned char result;
    result = func_02051d08(&self->big_field, self->unk_9E);
    self->unk_A1 = result;
    self->unk_9C = 0x10;
    func_ov111_0229efec((void *) self);
}

unsigned short func_ov111_0229f504(unsigned char *s)
{
    unsigned char c;
    c = s[0x9e];
    if (c == 0) {
        return 0;
    }
    return *(unsigned short *) (s + (c - 1) * 2 + 0x3d16);
}

int func_ov111_0229f4dc(unsigned char *p)
{
    if ((func_ov111_0229efd8((UnkStruct_0229f860 *) p, 1) == 0) || (p[0x9f] == p[0xa0])) {
        return 0;
    }
    return 1;
}

void func_ov111_0229f4c4(void *p)
{
    ((unsigned char *) p)[0x9f] = 0;
    ((unsigned char *) p)[0xa0] = 0;
    func_ov111_0229efb8(p, 1);
}

int func_ov111_0229f430(UnkStruct_0229f430 *a, int b)
{
    if (b == 0) {
        return 0;
    }
    if (func_ov002_022088ac(b)) {
        if (a->unk_9E != 0) {
            a->unk_9E--;
            return 1;
        }
    } else {
        if (func_ov002_0220889c(b)) {
            int res = func_02051c8c_unk((u16 *) ((char *) a + 0x3d16), 0x10);
            if (a->unk_9E + 1 > res) {
                goto ret_4;
            }
            a->unk_9E++;
            return 1;
        ret_4:
            return 4;
        }
    }
    if (func_ov002_022088cc(b)) {
        return 2;
    }
    if (func_ov002_022088bc(b)) {
        return 3;
    }
    return 0;
}

int func_ov111_0229f3ac(void *arg)
{
    int a;
    if (data_021fbe40[1] & 1) {
        goto body;
    }
    return 0;
body:
    a = func_ov095_02299a00((char *) arg + 0xac);
    if (a == -1) {
        return 0;
    }
    if (func_ov095_0229c448((char *) arg + 0xac, a, 9) == 0x106) {
        if (func_ov111_0229f660((unsigned char *) arg) != 0) {
            func_ov002_0220a1dc((char *) arg + 0x3d38);
            func_ov002_02208098((void *) (arg), 13);
            return 1;
        } else {
            return 0;
        }
    } else {
        func_ov095_0229c8e4((char *) arg + 0xac, a);
        func_ov111_0229f0ec(arg);
        return 1;
    }
}

int func_ov111_0229f358(UnkStruct_0229f358 *param)
{
    if (!(data_021fbe40[1] & 2)) {
        return 0;
    }
    if (func_ov111_0229fb8c((UnkStruct_0229fb8c *) param, 0) != 0) {
        func_ov095_0229bf3c(&param->unk_AC);
        param->unk_98 = param->unk_8D;
        func_ov002_02208098((void *) (param), 8);
    } else {
        func_ov111_022a09f8(param, 7, 0);
    }
    return 1;
}

int func_ov111_0229f2ec(unsigned char *arg)
{
    if ((data_021fbe40[1] & 0x100) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64((void *) (arg + 0xac), 0xc) != 0) {
        return 0;
    }
    func_ov111_0229f730((struct UnkStruct_0229f730 *) arg, 0x119);
    func_ov095_0229c8e4((void *) (arg + 0xac), 0x10a);
    func_ov111_0229f10c(arg);
    arg[0x98] = arg[0x8d];
    func_ov002_02208098((void *) (arg), 0xc);
    return 1;
}

int func_ov111_0229f288(struct UnkStruct_0229f288 *self)
{
    if (!((*(struct UnkStruct_0229f288_2 *) data_021fbe40).unk_02 & 0x200)) {
        return 0;
    }
    if (func_ov095_0229cf64((void *) (&self->unk_AC), 0xb) != 0) {
        return 0;
    }
    func_ov111_0229f730((struct UnkStruct_0229f730 *) self, 0x118);
    func_ov095_0229c8e4((void *) (&self->unk_AC), 0x109);
    self->unk_98 = self->unk_8D;
    func_ov002_02208098((void *) (self), 0xb);
    return 1;
}

int func_ov111_0229f24c(void *param)
{
    unsigned short *reg = (unsigned short *) ((unsigned char *) data_021fbe40);
    if ((reg[1] & 8) == 0) {
        return 0;
    }
    if (func_ov111_0229f660((unsigned char *) param) != 0) {
        func_ov111_0229f1d8(param);
        func_ov002_02208098((void *) (param), 13);
        return 1;
    }
    return 0;
}

void func_ov111_0229f1fc(Struct_ov111_0229f1fc *self)
{
    int a;
    int b;

    func_ov111_0229efb8(self, 2);
    func_ov095_02299aec(&self->unk_AC);
    a = func_ov095_02299b7c(&self->unk_AC);
    b = func_ov095_02299b38(&self->unk_AC);
    func_ov002_0220a0b4(&self->unk_3D38, a, b);
    func_ov002_0220a374(&self->unk_3D38, 1);
    func_ov111_0229f0a4(self);
}
