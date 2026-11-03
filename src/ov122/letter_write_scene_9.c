/* letter_write_scene_9: 13 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_022a116c @ 0x022a116c, 0xb4 bytes, Thumb
 * func_ov122_022a1110 @ 0x022a1110, 0x5c bytes, Thumb
 * func_ov122_022a1030 @ 0x022a1030, 0xe0 bytes, Thumb
 * func_ov122_022a0f78 @ 0x022a0f78, 0xb8 bytes, Thumb
 * func_ov122_022a0e90 @ 0x022a0e90, 0xe6 bytes, Thumb
 * func_ov122_022a0e4c @ 0x022a0e4c, 0x44 bytes, Thumb
 * func_ov122_022a0e04 @ 0x022a0e04, 0x46 bytes, Thumb
 * func_ov122_022a0df8 @ 0x022a0df8, 0xc bytes, Thumb
 * func_ov122_022a0dec @ 0x022a0dec, 0xc bytes, Thumb
 * func_ov122_022a0d84 @ 0x022a0d84, 0x68 bytes, Thumb
 * func_ov122_022a0cec @ 0x022a0cec, 0x98 bytes, Thumb
 * func_ov122_022a0be4 @ 0x022a0be4, 0x108 bytes, Thumb
 * func_ov122_022a0afc @ 0x022a0afc, 0xe8 bytes, Thumb
 */

#include "types.h"

typedef struct Work Work;

struct Work {
    char pad_00[0x8c];
    char byte;
    char pad_8D[0xc0 - 0x8c - 1];
    char arr[1];
};

extern int func_0206f56c(void);
extern void func_ov122_0229efd8(unsigned char *self, int param);
extern void func_ov122_0229f0a8(unsigned char *self);
extern int func_ov002_02208054(unsigned char *self, int param);
extern void func_ov122_0229ff2c(unsigned char *self);
extern int func_ov002_02208aec(unsigned char *base, unsigned char a, unsigned char b);
extern void func_ov002_022090b0(unsigned char *base, int param);
extern int func_ov002_02208a8c(unsigned char *base, unsigned char a, unsigned char b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov095_0229cce0(void *p);
extern int func_ov095_0229c54c(void *p, unsigned char a, unsigned char b);
extern int func_ov095_0229c448(void *p, int v, int n);
extern void func_ov095_0229c8e4(void *p, int v);
extern void func_ov095_0229bf3c(void *p);
extern int func_ov122_0229f958(void *);
extern void func_ov095_0229b3ec(void *);
extern void func_ov122_0229f89c(void *);
extern void *func_ov122_0229f634(void *);
extern int func_ov095_0229b3a0(void *, void *, unsigned char);
extern void func_ov122_0229f388(void *receiver);
extern void func_0200467c(int);
extern void func_ov122_022a15b8(void *, int, int);
extern void func_ov122_0229f9a8(void *);
extern void *func_ov122_0229f980(void *self);
extern int func_ov095_0229bb9c(void *receiver, int value);
extern int func_ov095_0229bb98(void *receiver, int value);
extern int func_ov095_0229bb94(void *receiver, int value);
extern void *func_ov122_0229f5a0(void *self);
extern void *func_ov122_0229f5f8(void *self);
extern int func_ov122_0229f5c8(void *self);
extern int func_ov095_0229bba0(void *obj, void *a, void *b, void *c);
extern void func_ov122_0229f590(void *self, int v);
extern int func_ov095_0229bc00(void *obj, void *a, int b, u8 *sav, int p4, int p5, int p6, int p7, int p8, int p9);
extern int func_ov095_0229bcec(void *obj, void *a, int b, u8 *sav, int p4, int p5, int p6, int p7);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov122_0229f454(void *p, int a);
extern void func_ov122_0229efc8(void *p, int a);
extern void func_ov122_0229f940(void *p);
extern void func_ov122_0229f2d0(void *p);
extern void func_ov122_0229f348(int a, int b);
extern void func_02051bf8(void *, int);
extern void func_02051c08(int, void *, int);
extern void func_ov095_022999f4(void *receiver);
extern void func_ov122_022a14c0(void *);
extern int func_ov122_0229efe8(void *self, int value);
extern void func_ov095_0229b394(void *p);
extern int func_02051c8c_unk(void *p, int n);
extern void func_ov095_022999e8(void *p);
extern void func_ov095_0229b388(void *p);
extern int func_ov095_0229ba44(void *, int, int);
extern int func_ov095_0229bebc(void *, int);

// The guard chain keeps a final dead compare, as in the original.

extern int func_ov002_02208014(void *receiver);
extern u8 func_ov002_02208008(void *);
extern int func_ov002_02207fe4(void *);
extern int func_ov095_02299a00(void *);
extern int func_ov095_02299a54(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a254(void *);
extern void func_ov002_0220a314(void *);
extern unsigned char *func_ov122_022a0054(void *);
extern void func_ov122_0229f250(void *);
extern int func_ov122_022a024c(void *);
extern int func_ov122_022a0204(void *);
extern int func_ov122_022a0168(void *);
extern int func_ov122_022a0098(void *);
extern int func_ov122_022a00fc(void *);
extern int func_ov122_022a006c(void *);

int func_ov122_022a0be4(char *a, int b);

void func_ov122_022a116c(unsigned char *self)
{
    unsigned int flag;
    int ret;

    if (func_0206f56c()) {
        func_ov122_0229efd8(self, 0x2000);
        func_ov122_0229f0a8(self);
        return;
    }

    if (func_ov002_02208054(self, 1)) {
        func_ov122_0229ff2c(self);
        return;
    }

    if (data_021fbdd8 && data_021fbddc) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag > 0) {
        ret = func_ov002_02208aec(self + 0x42b0, data_021f6c58, data_021f6c54);
        if (ret >= 0) {
            func_ov002_022090b0(self + 0x42b0, ret);
            self[0xb6] = (unsigned char) func_ov002_02208a8c(self + 0x42b0, self[0xb7], (unsigned char) ret);
            func_ov002_02208098((void *) (self), 0x17);
        } else {
            func_ov122_0229f0a8(self);
        }
    }
}

int func_ov122_022a1110(unsigned char *self)
{
    int r4, r6;

    func_ov095_0229cce0(self + 0xc0);

    r4 = func_ov095_0229c54c(self + 0xc0, data_021f6c58, data_021f6c54);

    if (r4 == -1) {
        return 0;
    }

    r6 = func_ov122_022a0be4((char *) self, func_ov095_0229c448(self + 0xc0, r4, 9));
    func_ov095_0229c8e4(self + 0xc0, r4);
    self += 0xc0;
    func_ov095_0229bf3c(self);

    return r6;
}

int func_ov122_022a1030(void *self, int param)
{
    if (func_ov122_0229f958(self) != 0) {
        func_ov095_0229b3ec((char *) self + 0xc0);
        func_ov122_0229f89c(self);
    } else {
        if (*(unsigned char *) ((char *) self + 0xac) != 0) {
            void *ret = func_ov122_0229f634(self);
            if (func_ov095_0229b3a0((char *) self + 0xc0, ret, *(unsigned char *) ((char *) self + 0xac)) == 0) {
                *(unsigned char *) ((char *) self + 0xad) = *(unsigned char *) ((char *) self + 0xac);
                *(unsigned char *) ((char *) self + 0xae) = (unsigned char) (*(unsigned char *) ((char *) self + 0xac) - 1);
                func_ov122_0229f89c(self);
            }
        } else {
            unsigned char *ret = func_ov122_0229f634(self);
            unsigned char b = *(unsigned char *) ((char *) self + 0xaa);
            if (b == 0) {
                unsigned char *ptr = *(unsigned char **) ((char *) self + 0xbc);
                if (*(unsigned char *) ((char *) ptr + 0xf8) == 0) {
                    goto ret0;
                }
            }
            if (b == 1) {
                unsigned char *ptr = *(unsigned char **) ((char *) self + 0xbc);
                if (*(unsigned char *) ((char *) ptr + 0xf8) == 0xa) {
                    goto ret0;
                }
            }
            if (*(unsigned short *) ret != 0) {
                goto set_fields;
            }
        ret0:
            if (param != 0) {
                func_ov122_0229f388((void *) self);
            }
            return 0;
        set_fields:
            *(unsigned char *) ((char *) self + 0xad) = 0;
            *(unsigned char *) ((char *) self + 0xae) = 1;
            func_ov122_0229f89c(self);
        }
    }

    func_0200467c(0x35);
    func_ov122_022a15b8(self, 0, 1);
    func_ov122_0229f9a8(self);
    return 1;
}

int func_ov122_022a0f78(void *self, int cmd)
{
    volatile int argument_values[2];
    void *r6;
    void *r4;
    void *r7;
    int x;

    r6 = func_ov122_0229f980(self);
    if (r6 == 0) {
        return 0;
    }

    switch (cmd) {
        case 0x103:
            r6 = (void *) func_ov095_0229bb9c((char *) self + 0xc0, (int) r6);
            break;
        case 0x104:
            r6 = (void *) func_ov095_0229bb98((char *) self + 0xc0, (int) r6);
            break;
        case 0x105:
            r6 = (void *) func_ov095_0229bb94((char *) self + 0xc0, (int) r6);
            break;
        default:
            break;
    }

    if (r6 == 0) {
        return 0;
    }

    r4 = func_ov122_0229f5a0(self);
    r7 = func_ov122_0229f5f8(self);
    x = func_ov122_0229f5c8(self);

    if ((argument_values[0] = (int) (x), argument_values[1] = (int) (0x2710),
         func_ov095_0229bba0((void *) ((char *) self + 0xc0), r7, r6, r4)) == 0) {
        return 0;
    }

    func_ov122_022a15b8(self, 0, 1);
    func_ov122_0229f9a8(self);
    return 1;
}

int func_ov122_022a0e90(void *self, int b, int c)
{
    u8 sav;
    u8 old;
    void *r7v;
    int x;
    u8 *p;

    sav = (u8) func_ov122_0229f5a0(self);
    old = sav;
    r7v = func_ov122_0229f5f8(self);
    x = func_ov122_0229f5c8(self);

    if (*((u8 *) self + 0xaa) == 2) {
        if (func_ov095_0229bc00((void *) ((char *) self + 0xc0), r7v, b, &sav, 0x40, 0x28, 4, 0xa0, 0, c) != 0) {
            func_ov122_0229f590(self, sav);
        } else {
            return 0;
        }
    } else {
        if (b == 0xa) {
            return 0;
        }
        if (func_ov095_0229bcec((void *) ((char *) self + 0xc0), r7v, b, &sav, x, 0xa0, 0, 1) != 0) {
            switch (*((u8 *) self + 0xaa)) {
                case 0:
                    if (old != sav) {
                        p = *(u8 **) ((char *) self + 0xbc);
                        *(p + 0xf8) = (u8) (*(p + 0xf8) + sav - old);
                    }
                    break;
                case 1:
                    p = *(u8 **) ((char *) self + 0xbc);
                    sav = (u8) (sav - *(p + 0xf8));
                    break;
                default:
                    break;
            }
            func_ov122_0229f590(self, sav);
        } else {
            return 0;
        }
    }
    return 1;
}

int func_ov122_022a0e4c(void *p, void *q)
{
    int v;
    if (func_ov122_0229f958(p)) {
        func_ov122_0229f89c(p);
        func_ov095_0229b3ec((char *) p + 0xc0);
    }
    v = func_ov122_022a0e90(p, (int) q, 1);
    func_ov122_022a15b8(p, 0, 1);
    func_ov122_0229f9a8(p);
    return v;
}

void func_ov122_022a0e04(Work *self)
{
    self->byte = 4;
    func_ov002_022080a0((void *) (self), 1);
    func_ov122_0229f454(self, 0);
    func_ov122_0229efc8(self, 4);
    func_ov122_0229f940(self);
    func_ov095_0229b3ec(self->arr);
    func_ov122_022a15b8(self, 1, 0);
    func_ov122_0229f2d0(self);
}

void func_ov122_022a0df8(int a)
{
    func_ov122_0229f348(a, 1);
}

void func_ov122_022a0dec(int a)
{
    func_ov122_0229f348(a, 0);
}

void func_ov122_022a0d84(char *self)
{
    unsigned char a, b;
    int min, diff;
    int result;

    if (func_ov122_0229f958(self) == 0) {
        return;
    }
    b = *(unsigned char *) (self + 0xae);
    a = *(unsigned char *) (self + 0xad);
    if (a > b) {
        min = b;
        diff = a - b;
    } else {
        min = a;
        diff = b - a;
    }
    func_02051bf8(self + 0x4230, 0x40);
    result = (int) func_ov122_0229f634(self);
    func_02051c08(result + 2 * min, self + 0x4230, diff);
    func_ov122_0229efd8((unsigned char *) self, 0x400);
    func_ov095_022999f4(self + 0xc0);
    func_ov122_022a14c0(self);
}

void func_ov122_022a0cec(void *self)
{
    int count;
    int i;
    int zero;

    if (func_ov122_0229efe8(self, 0x400) == 0) {
        return;
    }

    if (func_ov122_0229f958(self) != 0) {
        func_ov122_0229f89c(self);
    }

    func_ov095_0229b3ec((char *) self + 0xc0);
    func_ov095_0229b394((char *) self + 0xc0);

    count = func_02051c8c_unk((char *) self + 0x4230, 0x40);
    i = 0;
    zero = 0;

    while (i < count) {
        char *p = (char *) self + i * 2;
        unsigned short val = *(unsigned short *) (p + 0x4230);
        if (func_ov122_022a0e90(self, (unsigned short) val, zero) == 0) {
            if (i == 0) {
                func_ov122_0229f388(self);
            }
            i = count;
        }
        i++;
    }

    func_ov095_022999e8((char *) self + 0xc0);
    func_ov122_022a15b8(self, 0, 1);
    func_ov122_0229f9a8(self);
    self = (char *) self + 0xc0;
    func_ov095_0229b388(self);
}

int func_ov122_022a0be4(char *a, int b)
{
    int ret = 1;
    int t;

    t = func_ov095_0229ba44(a + 0xc0, b, 6);
    if (t != 0) {
        func_ov122_022a15b8(a, 0, ret);
        return t;
    }
    if (func_ov095_0229bebc(a + 0xc0, b)) {
        switch (b) {
            case 0x100:
                func_ov122_022a1030(a, ret);
                break;
            case 0x103:
            case 0x104:
            case 0x105:
                if (func_ov122_022a0f78(a, b) == 0) {
                    func_ov122_0229f388(a);
                }
                ret = 2;
                break;
            case 0x113:
                func_ov122_022a0df8((int) a);
                ret = 3;
                break;
            case 0x114:
                func_ov122_022a0dec((int) a);
                ret = 3;
                break;
            case 0x118:
                func_ov122_022a0d84((char *) a);
                ret = 2;
                break;
            case 0x119:
                func_ov122_022a0cec(a);
                ret = 2;
                break;
        }
    } else {
        if (func_ov122_022a0e4c(a, (void *) ((unsigned short) b)) == 0) {
            func_ov122_0229f388(a);
        }
        if (b == 0xa) {
            ret = 2;
        }
    }
    return ret;
}

void func_ov122_022a0afc(void *o)
{
    u8 f;

    if (func_ov002_02208014(o) != 0) {
        func_ov122_022a0054(o);
        return;
    }
    f = func_ov002_02208008(o);
    if (func_ov122_0229efe8(o, 0x10) == 1) {
        if (func_ov095_02299a00((char *) o + 0xc0) == 0x104) {
            if (func_ov002_02207fe4(o) != 0) {
                f = f & ~0x20;
            }
        }
    }
    switch (func_ov095_02299a54((char *) o + 0xc0, f)) {
        case 1:
            func_ov002_0220a2b4((char *) o + 0x4058);
            func_ov122_0229f250(o);
            break;
        case 2:
            func_ov002_0220a254((char *) o + 0x4058);
            func_ov122_0229f250(o);
            break;
        case 3:
            func_ov002_0220a314((char *) o + 0x4058);
            func_ov122_0229f250(o);
            break;
        case 0:
        default:
            if (func_ov122_022a024c(o) != 0) {
                return;
            }
            if (func_ov122_022a0204(o) != 0) {
                return;
            }
            if (func_ov122_022a0168(o) != 0) {
                return;
            }
            if (func_ov122_022a0098(o) != 0) {
                return;
            }
            if (func_ov122_022a00fc(o) != 0) {
                return;
            }
            if (func_ov122_022a006c(o) != 0) {
                return;
            }
            break;
    }
}
