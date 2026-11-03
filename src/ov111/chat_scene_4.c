/* chat_scene_4: 21 functions, module ov111
 * mwccarm 1.2/base -O4,s
 * func_ov111_022a0530 @ 0x022a0530, 0x80 bytes, Thumb
 * func_ov111_022a04cc @ 0x022a04cc, 0x64 bytes, Thumb
 * func_ov111_022a04ac @ 0x022a04ac, 0x20 bytes, Thumb
 * func_ov111_022a0460 @ 0x022a0460, 0x4c bytes, Thumb
 * func_ov111_022a02f8 @ 0x022a02f8, 0x168 bytes, Thumb
 * func_ov111_022a027c @ 0x022a027c, 0x7c bytes, Thumb
 * func_ov111_022a024c @ 0x022a024c, 0x30 bytes, Thumb
 * func_ov111_022a021c @ 0x022a021c, 0x30 bytes, Thumb
 * func_ov111_022a0204 @ 0x022a0204, 0x16 bytes, Thumb
 * func_ov111_022a01dc @ 0x022a01dc, 0x28 bytes, Thumb
 * func_ov111_022a01bc @ 0x022a01bc, 0x20 bytes, Thumb
 * func_ov111_022a0198 @ 0x022a0198, 0x24 bytes, Thumb
 * func_ov111_022a00f4 @ 0x022a00f4, 0xa4 bytes, Thumb
 * func_ov111_022a001c @ 0x022a001c, 0xd8 bytes, Thumb
 * func_ov111_0229fff4 @ 0x0229fff4, 0x28 bytes, Thumb
 * func_ov111_0229ff88 @ 0x0229ff88, 0x6c bytes, Thumb
 * func_ov111_0229ff60 @ 0x0229ff60, 0x26 bytes, Thumb
 * func_ov111_0229fed8 @ 0x0229fed8, 0x88 bytes, Thumb
 * func_ov111_0229fe0c @ 0x0229fe0c, 0xcc bytes, Thumb
 * func_ov111_0229fdf0 @ 0x0229fdf0, 0x1c bytes, Thumb
 * func_ov111_0229fd58 @ 0x0229fd58, 0x98 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022a0530 {
    unsigned char pad_00[0xac];
    unsigned char unk_AC[1];
    unsigned char pad_AD[0x3d38 - 0xac - 1];
    unsigned char unk_3D38;
} UnkStruct_022a0530;

struct SubType {
    int pad_00;
};

struct Param {
    unsigned char pad_00[0x9e];
    unsigned char unk_9E;
    unsigned char unk_9F;
    unsigned char unk_A0;
    unsigned char pad_A1[0x0b];
    struct SubType unk_AC;
};

typedef struct {
    char pad_00[0x98];
    unsigned char unk_98;
} ParamType;

typedef struct {
    unsigned char pad_00[0x9a];
    unsigned char unk_9A;
    unsigned char pad_9B[2];
    unsigned char unk_9D;
    unsigned char pad_9E[4];
    unsigned char unk_A2;
    unsigned char pad_A3[9];
    unsigned char unk_AC;
} UnkStruct_022a00f4;

struct UnkStruct_0229fe0c {
    u8 pad_00[0x9a];
    u8 unk_9A;
    u8 unk_9B;
    u8 unk_9C;
    u8 pad_9D[4];
    u8 unk_A1;
    u8 pad_A2[10];
    u8 obj[1];
};

typedef struct {
    unsigned char pad_00[0x2c];
    int unk_2C;
    unsigned char _pad1[8];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad_3A[22];
    int unk_50;
    unsigned char pad_54[1];
    unsigned char unk_55;
} ObjA;

typedef struct {
    unsigned char pad_00[0x9f];
    unsigned char unk_9F;
    unsigned char unk_A0;
    unsigned char _pad1[7];
    ObjA *a8;
} UnkStruct_0229fd58;

extern int func_0208e484(void *);
extern void *func_ov095_02299a00(void *);
extern int func_ov095_0229c448(void *, void *, int);
extern int func_ov111_0229f730(void *, int);
extern void func_ov095_0229bf3c(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov095_0229c8e4(void *, void *);
extern void func_ov095_0229cce0(void *);
extern void func_ov111_0229f0cc(void *);
extern unsigned short data_021fbe40;
extern int func_ov095_0229bf0c(void *p);
extern void *func_ov095_0229c548(void *p);
extern void func_ov111_0229f0a4(char *ptr);
extern int func_ov111_0229efd8(void *p, int val);
extern void func_ov111_0229f10c(void *p);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern unsigned int func_ov111_0229f430(void *, int);
extern void func_ov095_0229b3ec(void *);
extern void func_ov111_0229f4c4(void *);
extern void func_ov111_0229f524(void *);
extern void func_ov111_0229fd08(void *);
extern void func_0200467c(int);
extern void func_ov095_0229a148(void *);
extern void func_ov111_0229efb8(void *, int);
extern void func_ov111_0229f164(void *);
extern int func_ov002_02209f00(void *);
extern void func_ov095_0229a154(void *, int);
extern void func_ov002_0220a254(void *);
extern void func_ov095_0229a170(void *, int);
extern int func_ov111_0229f288(void *);
extern int func_ov111_0229f2ec(void *);
extern int func_ov111_0229f358(void *);
extern void func_ov111_0229efc8(void *, int);
extern int func_ov111_0229f24c(void *);
extern void func_ov111_0229efec(struct Param *p);
extern void func_ov111_0229f1d8(void *unused0);
extern int func_0206fe60(void);
extern int func_ov095_0229af84(void *);
extern int func_020957b4(unsigned char *);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov095_0229afac(unsigned char *ptr);
extern int func_0206fe54(void);
extern void func_ov002_0220a164(const void *ptr);
extern int func_0208e4bc(const void *ptr);
extern void func_ov111_0229fcb0(void *self);
extern void func_ov111_0229f994(void *self);
extern int func_ov095_0229bf48(void *);
extern int func_ov002_0220b8ac(void *, int);
extern void func_ov095_0229c084(void *, int);
extern int func_0206f504(void);
extern void func_02051c08(int, void *, int);
extern void func_020953a0(void);
extern int func_020ee45c(void *);
extern int func_ov090_02298f74(int);
extern void func_ov095_0229c05c(void *);
extern void func_0209539c(void);
extern int *data_021fbe94;
extern int data_ov111_022a0f78[];
extern void *func_02064b2c(int, int *, int, int);
extern void MI_CpuCopy8(char *, char *, int);
extern void func_0206fd60(char *, int, int, int, int, int, int);
extern void func_020e993c(int *, void *);
extern void func_ov095_0229bf70(char *);
extern void *func_ov002_02207f60(void *);
extern void func_ov095_0229b1c8(void *, int, void *, int);
extern void func_ov095_0229b0d8(void *, int, void *);
extern void func_ov095_0229b090(void *, int, void *, int, int);
extern int func_ov095_0229af58(void *, int, void *, int);
extern void func_ov095_0229aeec(void *, int, void *);
extern void func_020a8fb8(void *object);
extern void *func_020a9034(int a, int b, int c);
extern int func_ov111_0229f4dc(void *p);
extern void func_02051608(void *p, int a, int b, int c, int d);

void func_ov111_022a0204(void *p);
void func_ov111_0229fed8(char *p, int n);
void func_ov111_0229fdf0(void *self);

void func_ov111_022a0530(UnkStruct_022a0530 *self)
{
    void *ptr;
    int val;

    if (func_0208e484(&self->unk_3D38) == 0) {
        return;
    }

    ptr = func_ov095_02299a00(&self->unk_AC);
    val = func_ov111_0229f730(self, func_ov095_0229c448(&self->unk_AC, ptr, 9));

    if (val == 3) {
        return;
    }
    if (val == 1) {
        if (data_021fbe40 & 1) {
            func_ov095_0229bf3c(&self->unk_AC);
            func_ov002_02208098((void *) (self), 6);
            self = (UnkStruct_022a0530 *) ((char *) self + 0xac);
            func_ov095_0229c8e4(self, ptr);
            return;
        }
    }
    func_ov095_0229cce0(&self->unk_AC);
    if (val != 4) {
        func_ov111_0229f0cc(self);
    }
}

void func_ov111_022a04cc(void *self)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov095_0229cce0((char *) self + 0xac);
        func_ov111_0229f0cc(self);
    } else if (func_ov095_0229bf0c((char *) self + 0xac) != 0) {
        void *x = func_ov095_0229c548((char *) self + 0xac);
        func_ov111_0229f730(self, (int) ((void *) func_ov095_0229c448((char *) self + 0xac, x, 9)));
        func_ov095_0229c8e4((char *) self + 0xac, x);
    }
}

void func_ov111_022a04ac(char *param)
{
    if (func_0208e484((void *) (param + 0x3d38))) {
        func_ov111_0229f0a4(param);
    }
}

void func_ov111_022a0460(unsigned char *p)
{
    if ((data_021fbe40 & 2) == 0) {
        unsigned char *q;
        unsigned char b;
        q = p + 0x98;
        b = *q;
        func_ov002_02208098((void *) (p), b);
    } else {
        if (func_ov095_0229bf0c(p + 0xac)) {
            func_ov111_0229f730(p, 0x100);
            if (func_ov111_0229efd8(p, 2)) {
                func_ov111_0229f10c(p);
            }
        }
    }
}

void func_ov111_022a02f8(void *self)
{
    unsigned char *ptr;
    ptr = (unsigned char *) self;
    if (func_ov002_02208014(self) != 0) {
        func_ov111_022a0204(self);
        return;
    }
    {
        int val = func_ov002_02208008(self);
        unsigned int action = func_ov111_0229f430(self, val);
        switch (action) {
            case 1:
                func_ov095_0229b3ec(((char *) self) + 0xac);
                func_ov111_0229f4c4(self);
                func_ov111_0229f524(self);
                func_ov111_0229fd08(self);
                func_ov111_0229f10c(self);
                func_0200467c(0xb);
                break;

            case 4:
                func_ov095_0229a148(((char *) self) + 0xac);
                func_ov111_0229efb8(self, 2);
                func_ov002_02208098((void *) (self), 3);
                func_ov111_0229f164(self);
                break;

            case 2:
                func_ov095_0229a154(((char *) self) + 0xac, func_ov002_02209f00(ptr + 0x3d38));
                func_ov111_0229efb8(self, 2);
                func_ov002_02208098((void *) (self), 3);
                func_ov002_0220a254(((unsigned char *) self) + 0x3d38);
                func_ov111_0229f164(self);
                break;

            case 3:
                func_ov095_0229a170(((char *) self) + 0xac, func_ov002_02209f00(((char *) self) + 0x3d38));
                func_ov111_0229efb8(self, 2);
                func_ov002_02208098((void *) (self), 3);
                func_ov111_0229f164(self);
                break;

            default:

            case 0:
                if (func_ov111_0229f288(self) != 0) {
                    return;
                }
                if (func_ov111_0229f2ec(self) != 0) {
                    return;
                }
                {
                    unsigned char b = *((unsigned char *) (((char *) self) + 0x9e));
                    if (func_ov111_0229f358(self) != 0) {
                        if (b == (*((unsigned char *) (((char *) self) + 0x9e)))) {
                            return;
                        }
                        func_ov111_0229f10c(self);
                        return;
                    }
                    if (((*(struct { unsigned short f0; unsigned short f2; } *) &data_021fbe40).f2 & 1) != 0) {
                        func_ov002_02208098((void *) (self), 0xa);
                        func_ov111_0229efc8(self, 1);
                        *((unsigned char *) (((char *) self) + 0x9f)) = *((unsigned char *) (((char *) self) + 0x9e));
                        *((unsigned char *) (((char *) self) + 0xa0)) = *((unsigned char *) (((char *) self) + 0x9e));
                        return;
                    } else if (func_ov111_0229f24c(self) != 0) {
                        return;
                    }
                }
                break;
        }
    }
}

void func_ov111_022a027c(struct Param *p)
{
    if (!(data_021fbe40 & 1)) {
        func_ov002_02208098((void *) (p), 9);
        if (p->unk_9F == p->unk_A0) {
            func_ov111_0229efb8((void *) p, 1);
        }
    } else {
        if ((int) func_ov111_0229f430((void *) p, func_ov002_02208008((void *) p)) == 1) {
            func_ov095_0229b3ec((void *) (&p->unk_AC));
            func_ov111_0229f524((void *) p);
            p->unk_A0 = p->unk_9E;
            func_ov111_0229f10c((void *) p);
            func_0200467c(21);
        }
    }
    func_ov111_0229fd08((void *) p);
    func_ov111_0229efec(p);
}

void func_ov111_022a024c(void *param)
{
    if ((data_021fbe40 & 0x200) == 0) {
        unsigned char c = *(unsigned char *) ((char *) param + 0x98);
        func_ov002_02208098((void *) (param), c);
        func_ov111_0229efec((struct Param *) param);
    }
}

void func_ov111_022a021c(ParamType *param)
{
    if ((data_021fbe40 & 0x100) == 0) {
        func_ov002_02208098((void *) (param), param->unk_98);
        func_ov111_0229efec((struct Param *) param);
    }
}

void func_ov111_022a0204(void *p)
{
    func_ov111_0229f1d8(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov111_022a01dc(void *r0)
{
    extern void func_ov002_02207fc0(void *);
    extern void func_ov111_0229f1fc(void *);
    extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
    extern void func_ov111_0229fd08(void *);

    void *r4 = r0;
    func_ov002_02207fc0(r4);
    func_ov111_0229f1fc(r4);
    func_ov002_02208098((void *) (r4), 3);
    func_ov111_0229fd08(r4);
    func_ov111_0229efec((struct Param *) r4);
}

void func_ov111_022a01bc(int param)
{
    if (func_0206fe60() != 0) {
        func_ov111_022a0204((void *) param);
    } else {
        func_ov111_022a01dc((void *) param);
    }
}

void func_ov111_022a0198(unsigned char *s)
{
    unsigned char buf[8];
    buf[0] = func_ov095_0229af84(s + 0xac);
    func_020957b4(buf);
    s[0xa2] = 0x14;
}

void func_ov111_022a00f4(UnkStruct_022a00f4 *self)
{
    if (func_0206fe60() != 0) {
        unsigned int flag = (data_021fbdd8 && data_021fbddc);
        if (flag > 0) {
            if (self->unk_A2 == 0) {
                if (func_ov095_0229afac(&self->unk_AC) != 0) {
                    func_ov111_022a0198((unsigned char *) self);
                }
            }
        }
    }

    if (self->unk_9A < 4) {
        self->unk_9A++;
        func_ov111_0229fed8((char *) self, self->unk_9A);
        self->unk_9D = 3;
    } else {
        if (self->unk_9D != 0) {
            self->unk_9D--;
        } else {
            func_ov095_0229b3ec((void *) (&self->unk_AC));
            func_ov002_02208098((void *) (self), 0xe);
        }
    }
}

void func_ov111_022a001c(unsigned char *self)
{
    if (func_0206fe60()) {
        unsigned int flag = (data_021fbdd8 != 0) && (data_021fbddc != 0);
        if (flag > 0) {
            if (self[0xa2] == 0 && func_ov095_0229afac((unsigned char *) (self + 0xac)) != 0) {
                func_ov111_022a0198((unsigned char *) self);
            }
        }
    }
    if (self[0x9a] != 0) {
        if (self[0x9a] == 3) {
            func_ov111_0229fcb0(self);
        }
        self[0x9a] = self[0x9a] - 1;
        func_ov111_0229fed8((char *) self, (unsigned char) self[0x9a]);
        if (self[0x9a] == 1) {
            if (func_0206fe54()) {
                func_ov002_0220a164(self + 0x3d38);
            }
        }
    } else {
        func_ov111_0229f994(self);
        func_ov111_0229fd08(self);
        if (func_0206fe60()) {
            func_ov002_02208098((void *) (self), 0);
        } else if (func_0208e4bc(self + 0x3d38)) {
            func_ov002_02208098((void *) (self), 7);
        } else {
            func_ov111_022a01dc(self);
        }
    }
}

void func_ov111_0229fff4(void *obj)
{
    func_ov095_0229bf48((char *) obj + 0xac);
    if (func_ov002_0220b8ac((char *) obj + 0x3d9c, 1) != 0) {
        func_ov111_022a01bc((int) obj);
    }
}

void func_ov111_0229ff88(void *self)
{
    *(unsigned short *) ((char *) self + 0xa4) = 0;
    *(unsigned char *) ((char *) self + 0x99) = 0;
    *(unsigned char *) ((char *) self + 0x9a) = 0;
    *(unsigned char *) ((char *) self + 0x9b) = 0;
    *(unsigned char *) ((char *) self + 0xa2) = 0;
    func_ov111_0229f994(self);
    *(int *) ((char *) self + 0xa8) = 0;
    func_ov095_0229c084((char *) self + 0xac, 0);
    func_02051c08(func_0206f504(), (char *) self + 0x3d16, 0x10);
    func_020953a0();
    if (func_ov090_02298f74(func_020ee45c(self))) {
        func_ov111_0229efc8(self, 0x20);
    }
}

void func_ov111_0229ff60(void *param)
{
    void *r4 = param;
    func_ov111_0229fdf0(r4);
    func_ov095_0229c05c((char *) r4 + 0xac);
    if (func_ov111_0229efd8(r4, 0x10) == 0) {
        func_0209539c();
    }
}

void func_ov111_0229fed8(char *p, int n)
{
    char *res;
    int *g;
    char *base;

    g = data_021fbe94;
    res = func_02064b2c((n == 0) ? data_ov111_022a0f78[0] : data_ov111_022a0f78[n - 1], g, -4, 0);
    base = p + 0x24d4;
    MI_CpuCopy8(res + 0x100, base + 0x100, 0x140);

    if (n == 1) {
        func_0206fd60(base, 0, 4, 0x1f, 9, 5, 6);
    }

    func_020e993c(g, res);
    p += 0xac;
    func_ov095_0229bf70(p);
}

void func_ov111_0229fe0c(struct UnkStruct_0229fe0c *self)
{
    u8 *work;
    int mode;

    work = (u8 *) func_ov002_02207f60(self) + 0x60;

    func_ov095_0229b1c8(self->obj, 0x80, work, 2);
    func_ov095_0229b0d8(self->obj, 0x80, work);

    if (self->unk_9A != 0) {
        if (self->unk_9B < 2) {
            self->unk_9B++;
        }
        mode = 7;
    } else {
        if (self->unk_9B != 0) {
            self->unk_9B--;
        }
        mode = 6;
    }

    func_ov095_0229b090(self->obj, 0x80, work, mode, self->unk_9B);
    self->unk_9C++;

    if (self->unk_9A == 0 && (self->unk_9C & 0x10) != 0) {
        func_ov095_0229af58(self->obj, self->unk_A1 + 0x18, work - 0x38, 2);
    }

    func_ov095_0229aeec(self->obj, 0x80, work);
}

void func_ov111_0229fdf0(void *self)
{
    if (*(int *) ((char *) self + 0xa8) != 0) {
        func_020a8fb8((void *) (*(int *) ((char *) self + 0xa8)));
        *(int *) ((char *) self + 0xa8) = 0;
    }
}

void func_ov111_0229fd58(UnkStruct_0229fd58 *p)
{
    if (p->a8 == 0) {
        p->a8 = func_020a9034(0x13d, 0x15, 2);
        if (p->a8 != 0) {
            p->a8->unk_2C = 3;
            p->a8->unk_50 = 1;
            p->a8->unk_55 = 0;
            p->a8->unk_39 = 2;
            p->a8->unk_38 = 1;
            if (func_ov111_0229f4dc(p) != 0) {
                unsigned char b = p->unk_A0;
                unsigned char a = p->unk_9F;
                int min;
                int diff;
                if (a > b) {
                    min = b;
                    diff = a - b;
                } else {
                    min = a;
                    diff = b - a;
                }
                func_02051608(p->a8, 2, 1, min, diff);
            }
        }
    }
}
