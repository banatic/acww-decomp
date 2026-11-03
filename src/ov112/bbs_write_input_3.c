/* bbs_write_input_3: 18 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_022a0fc4 @ 0x022a0fc4, 0x140 bytes, Thumb
 * func_ov112_022a0f88 @ 0x022a0f88, 0x3c bytes, Thumb
 * func_ov112_022a0f4c @ 0x022a0f4c, 0x3c bytes, Thumb
 * func_ov112_022a0eec @ 0x022a0eec, 0x60 bytes, Thumb
 * func_ov112_022a0e90 @ 0x022a0e90, 0x5c bytes, Thumb
 * func_ov112_022a0e24 @ 0x022a0e24, 0x6c bytes, Thumb
 * func_ov112_022a0d6c @ 0x022a0d6c, 0xb8 bytes, Thumb
 * func_ov112_022a0d40 @ 0x022a0d40, 0x2c bytes, Thumb
 * func_ov112_022a0c6c @ 0x022a0c6c, 0xd4 bytes, Thumb
 * func_ov112_022a0c10 @ 0x022a0c10, 0x5c bytes, Thumb
 * func_ov112_022a0be8 @ 0x022a0be8, 0x28 bytes, Thumb
 * func_ov112_022a0b84 @ 0x022a0b84, 0x64 bytes, Thumb
 * func_ov112_022a0ab0 @ 0x022a0ab0, 0xd4 bytes, Thumb
 * func_ov112_022a0a3c @ 0x022a0a3c, 0x74 bytes, Thumb
 * func_ov112_022a0a0c @ 0x022a0a0c, 0x30 bytes, Thumb
 * func_ov112_022a09dc @ 0x022a09dc, 0x30 bytes, Thumb
 * func_ov112_022a09b8 @ 0x022a09b8, 0x24 bytes, Thumb
 * func_ov112_022a097c @ 0x022a097c, 0x3c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022a0fc4 {
    unsigned char pad_00[0x384];
    unsigned char unk_384;
    unsigned char pad_385[0x3eaf];
    unsigned char unk_4234;
    unsigned char pad_4235[0x47];
    unsigned char unk_427C;
} UnkStruct_022a0fc4;

typedef struct {
    char pad_00[0xbe];
    unsigned char unk_BE;
    unsigned char unk_BF;
} UnkStruct_022a0eec;

struct UnkStruct_022a0ab0 {
    u8 pad_00[0xbd];
    u8 unk_BD;
    u8 unk_BE;
    u8 unk_BF;
};

typedef struct {
    unsigned char pad_00[0xbd];
    unsigned char unk_BD;
    unsigned char unk_BE;
    unsigned char unk_BF;
} UnkStruct_022a0a3c;

typedef struct {
    char pad_00[0xc1];
    unsigned char unk_C1;
} Param_t;

typedef struct {
    char pad_00[0xc1];
    unsigned char byte_at_c1;
} UnkStruct_022a09dc;

extern int func_ov002_02208054(void *p, int a);
extern unsigned char *func_ov112_0229ff1c(void *p);
extern int func_ov095_0229bf48(void *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern int func_ov002_0220a784(void *p, int n);
extern void func_ov112_022a0068(void *p);
extern void func_ov112_022a0028(void *p);
extern int func_ov095_0229aff0(void *p);
extern void func_ov095_0229c22c(void *p, int a, int b, int c);
extern void func_ov112_0229fd20(void *p);
extern int func_ov112_0229f788(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov095_0229b3ec(void *p);
extern int func_ov112_0229fa5c(void *p);
extern void func_ov002_0220a574(void *p);
extern void func_ov112_0229f8e4(void *p);
extern int func_ov112_0229fa2c(void *self);
extern int func_ov112_022a04b8(void *p);
extern void func_ov112_0229f784(void *receiver);
extern int func_ov002_0220a568(char *);
extern unsigned char *func_ov112_0229ff38(char *);
extern void func_ov112_0229f9bc(char *);
extern void func_ov112_0229f984(char *);
extern void func_ov112_0229fe50(UnkStruct_022a0eec *self, int val);
extern int func_ov112_0229f730(UnkStruct_022a0eec *self);
extern void func_0200467c(int cmd);
extern void func_ov112_0229fab4(UnkStruct_022a0eec *self);
extern int func_ov095_0229bf0c(void *p);
extern int func_ov095_0229c548(void *p);
extern void func_ov095_0229c8e4(void *p, int x);
extern void func_ov112_0229fe84(char *p);
extern void func_ov112_0229ffdc(char *p);
extern void func_ov112_0229ffa0(char *p);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(const void *);
extern int func_ov095_02299a54(const void *, int);
extern void func_ov112_0229f35c(const void *);
extern void func_ov002_0220a2b4(const void *);
extern void func_ov002_0220a254(const void *);
extern void func_ov002_0220a314(const void *);
extern int func_ov112_022a0710(const void *);
extern int func_ov112_022a06b8(const void *);
extern int func_ov112_022a0620(const void *);
extern int func_ov112_022a0548(const void *);
extern int func_ov112_022a05b0(const void *);
extern int func_ov112_022a051c(const void *);
extern int func_ov002_02209f64(void *);
extern void func_ov112_022a19ec(void *);
extern int func_0208e484(void *p);
extern int func_ov095_02299a00(void *p);
extern int func_ov095_0229c448(void *p, int a, int b);
extern void func_ov002_0220a4bc(void *receiver);
extern int func_ov112_0229f900(void *self);
extern void func_ov112_0229fe60(void *self, int a);
extern int func_ov112_022a03ac(void *self, int n);
extern void func_ov095_0229bf3c(void *p);
extern void func_ov095_0229cce0(void *p);
extern void func_ov112_0229f270(void *self);
extern void func_ov112_0229f250(void *);
extern int func_ov112_022a02f4(void *, int);
extern int func_ov112_0229fe70(void *, int);
extern void func_ov112_0229f2bc(void *);
extern void func_ov112_0229f3e0(void *);
extern u16 data_021fbe40[2];
extern int func_ov112_0229f56c(struct UnkStruct_022a0ab0 *self, int arg);
extern void func_ov112_0229f668(struct UnkStruct_022a0ab0 *self);
extern void func_ov112_0229f488(struct UnkStruct_022a0ab0 *self);
extern int func_0208e930(void *);
extern void func_ov112_0229f92c(void *ptr);

void func_ov112_022a0fc4(UnkStruct_022a0fc4 *self)
{
    int r4;
    unsigned int isBoth;
    int r6;
    int ret;

    if (func_ov002_02208054(self, 1)) {
        func_ov112_0229ff1c(self);
        return;
    }

    r4 = 0;
    if (func_ov095_0229bf48(&self->unk_384)) {
        r4 = 1;
    }

    isBoth = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (isBoth > 0) {
        r6 = data_021f6c54;

        if (func_ov002_0220a784(&self->unk_427C, 9)) {
            func_ov112_022a0068(self);
            return;
        }

        if (func_ov002_0220a784(&self->unk_427C, 8)) {
            func_ov112_022a0028(self);
            return;
        }

        if (func_ov095_0229aff0(&self->unk_384)) {
            func_ov095_0229c22c(&self->unk_384, 9, 6, 1);
            func_ov112_0229fd20(self);
            return;
        }

        if (func_ov112_0229f788(self)) {
            func_ov002_02208098(self, 3);
            func_ov095_0229b3ec(&self->unk_384);
            func_ov112_0229fd20(self);
            return;
        }

        if (func_ov112_0229fa5c(self)) {
            func_ov002_0220a574(&self->unk_4234);
            func_ov002_02208098(self, 1);
            func_ov112_0229f8e4(self);
            func_ov112_0229fd20(self);
            return;
        }

        if (func_ov112_0229fa2c(self)) {
            func_ov002_0220a574(&self->unk_4234);
            func_ov002_02208098(self, 2);
            func_ov112_0229f8e4(self);
            func_ov112_0229fd20(self);
            return;
        }

        if (r6 >= 0x48 && r4 == 0) {
            ret = func_ov112_022a04b8(self);
            if (ret != 0 && ret == 1) {
                func_ov002_02208098(self, 4);
            }
        }
    }
}

void func_ov112_022a0f88(char *p)
{
    p[0xbc] = 0;
    if (data_021fbdd8 == 0) {
        func_ov112_0229f784(p);
        func_ov002_0220a568(p + 0x4234);
        func_ov112_0229ff38(p);
    } else {
        func_ov112_0229f9bc(p);
    }
}

void func_ov112_022a0f4c(char *p)
{
    p[0xbc] = 0;
    if (data_021fbdd8 == 0) {
        func_ov112_0229f784(p);
        func_ov002_0220a568(p + 0x4234);
        func_ov112_0229ff38(p);
    } else {
        func_ov112_0229f984(p);
    }
}

void func_ov112_022a0eec(UnkStruct_022a0eec *self)
{
    int result;
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) self, 0);
        if (self->unk_BE == self->unk_BF) {
            func_ov112_0229fe50(self, 0x100);
        }
        result = 1;
    } else {
        result = func_ov112_0229f730(self);
        if (result != 0) {
            func_0200467c(0x15);
        }
    }
    if (result != 0) {
        func_ov112_0229fab4(self);
        func_ov112_0229fd20((void *) self);
    }
}

void func_ov112_022a0e90(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 0);
        return;
    }
    if (func_ov095_0229bf0c((char *) self + 0x384) != 0) {
        int x = func_ov095_0229c548((char *) self + 0x384);
        void *ret = (void *) func_ov095_0229c448((char *) self + 0x384, x, 9);
        func_ov112_022a03ac(self, (int) ret);
        func_ov095_0229c8e4((char *) self + 0x384, x);
    }
}

void func_ov112_022a0e24(char *self)
{
    unsigned int flag;

    if (func_ov002_02208054((void *) self, 1)) {
        func_ov112_0229fe84(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc);
    if (flag > 0) {
        if (func_ov002_0220a784((void *) (self + 0x427c), 3)) {
            func_ov112_0229ffdc(self);
            return;
        }
        if (func_ov002_0220a784((void *) (self + 0x427c), 4)) {
            func_ov112_0229ffa0(self);
        }
    }
}

void func_ov112_022a0d6c(char *self)
{
    int v;

    if (func_ov002_02208014(self) != 0) {
        func_ov112_0229ff38((char *) self);
        return;
    }

    v = func_ov095_02299a54(self + 0x384, func_ov002_02208008(self));

    switch (v) {
        case 1:
            func_ov002_0220a2b4(self + 0x4448);
            func_ov112_0229f35c(self);
            break;
        case 2:
            func_ov002_0220a254(self + 0x4448);
            func_ov112_0229f35c(self);
            break;
        case 3:
            func_ov002_0220a314(self + 0x4448);
            func_ov112_0229f35c(self);
            break;
        case 0:
        default:
            if (func_ov112_022a0710(self) != 0) {
                return;
            }
            if (func_ov112_022a06b8(self) != 0) {
                return;
            }
            if (func_ov112_022a0620(self) != 0) {
                return;
            }
            if (func_ov112_022a0548(self) != 0) {
                return;
            }
            if (func_ov112_022a05b0(self) != 0) {
                return;
            }
            if (func_ov112_022a051c(self) != 0) {
                return;
            }
    }
}

void func_ov112_022a0d40(void *obj)
{
    if (func_ov002_02209f64((char *) obj + 0x4448) == 0) {
        func_ov002_02208098(obj, *(unsigned char *) ((char *) obj + 0xC1));
        func_ov112_022a19ec(obj);
    }
}

void func_ov112_022a0c6c(char *self)
{
    int a;
    int n;
    int m;

    if (func_0208e484(self + 0x4448) != 0) {
        a = func_ov095_02299a00(self + 0x384);
        n = func_ov095_0229c448(self + 0x384, a, 9);
        if (n == 0x112) {
            func_ov002_02208098(self, 0x10);
            func_ov002_0220a574(self + 0x4234);
            func_ov002_0220a4bc((void *) ((char *) self + 0x4234));
            if (func_ov112_0229f900(self) != 0) {
                func_ov112_0229fd20(self);
            }
            func_ov112_0229f8e4(self);
            func_ov112_0229fe60(self, 0x1000);
        } else {
            m = func_ov112_022a03ac(self, n);
            if (m == 1 && ((*(u16 *) data_021fbe40) & 1) != 0) {
                func_ov095_0229bf3c(self + 0x384);
                func_ov002_02208098(self, 9);
                func_ov095_0229c8e4(self + 0x384, a);
            } else if (m != 3) {
                if (m == 4) {
                    func_ov095_0229cce0(self + 0x384);
                } else {
                    func_ov112_0229f270(self);
                }
            }
        }
    }
}

void func_ov112_022a0c10(void *self)
{
    int r;

    if (!((*(unsigned short *) data_021fbe40) & 1)) {
        func_ov112_0229f270(self);
        return;
    }
    if (func_ov095_0229bf0c((char *) self + 0x384) == 0) {
        return;
    }
    r = func_ov095_0229c548((char *) self + 0x384);
    func_ov112_022a03ac(self, func_ov095_0229c448((char *) self + 0x384, r, 9));
    func_ov095_0229c8e4((char *) self + 0x384, r);
}

void func_ov112_022a0be8(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x4448)) {
        func_ov112_0229f250(arg0);
        func_ov002_02208098(arg0, 6);
    }
}

void func_ov112_022a0b84(void *this)
{
    if (((*(unsigned short *) data_021fbe40) & 2) == 0) {
        func_ov002_02208098(this, ((char *) this)[0xc1]);
    } else {
        if (func_ov095_0229bf0c((char *) this + 0x384) != 0) {
            if (func_ov112_022a02f4(this, 0) != 0) {
                if (func_ov112_0229fe70(this, 0x800) != 0) {
                    func_ov112_0229f2bc(this);
                }
            } else {
                func_ov112_0229f3e0(this);
                func_ov112_022a0028(this);
            }
        }
    }
}

void func_ov112_022a0ab0(struct UnkStruct_022a0ab0 *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov112_0229ff38((char *) self);
        return;
    }

    if (func_ov112_0229f56c(self, func_ov002_02208008((const void *) self)) != 0) {
        func_ov112_0229f8e4((void *) self);
        func_ov112_0229f668(self);
        func_ov112_0229f2bc((void *) self);
        func_ov112_0229f488(self);
        func_0200467c(0xb);
        return;
    }

    if (func_ov112_022a0620((const void *) self) != 0) {
        return;
    }

    {
        u8 old = self->unk_BD;

        if (func_ov112_022a06b8((const void *) self) != 0) {
            if (old != self->unk_BD) {
                func_ov112_0229f2bc((void *) self);
            }
            return;
        }
    }

    if ((data_021fbe40[1] & 1) != 0) {
        func_ov002_02208098((void *) self, 0xd);
        func_ov112_0229fe60((void *) self, 0x100);
        self->unk_BE = self->unk_BD;
        self->unk_BF = self->unk_BD;
    }

    if (func_ov112_022a0548((const void *) self) != 0) {
        return;
    }
    if (func_ov112_022a05b0((const void *) self) != 0) {
        return;
    }
    if (func_ov112_022a051c((const void *) self) != 0) {
        return;
    }
}

void func_ov112_022a0a3c(UnkStruct_022a0a3c *obj)
{
    if (!((*(unsigned short *) data_021fbe40) & 1)) {
        func_ov002_02208098(obj, 0xc);
        if (obj->unk_BE != obj->unk_BF) {
            return;
        }
        func_ov112_0229fe50((UnkStruct_022a0eec *) obj, 0x100);
    } else {
        int ret = func_ov002_02208008((const void *) obj);
        if (func_ov112_0229f56c((struct UnkStruct_022a0ab0 *) obj, ret) != 0) {
            obj->unk_BF = obj->unk_BD;
            func_ov112_0229fd20(obj);
            func_ov112_0229f668((struct UnkStruct_022a0ab0 *) obj);
            func_ov112_0229f2bc(obj);
            func_0200467c(0x15);
        }
    }
}

void func_ov112_022a0a0c(Param_t *param)
{
    if (((*(unsigned short *) data_021fbe40) & 0x200) == 0) {
        func_ov002_02208098(param, param->unk_C1);
        func_ov112_0229f488((struct UnkStruct_022a0ab0 *) param);
    }
}

void func_ov112_022a09dc(UnkStruct_022a09dc *self)
{
    if (!((*(unsigned short *) data_021fbe40) & 0x100)) {
        func_ov002_02208098((void *) self, self->byte_at_c1);
        func_ov112_0229f488((struct UnkStruct_022a0ab0 *) self);
    }
}

void func_ov112_022a09b8(void *param)
{
    if (func_0208e930((char *) param + 0x4234)) {
        func_ov002_02208098(param, 0x11);
    }
}

void func_ov112_022a097c(void *param)
{
    if (((*(unsigned short *) data_021fbe40) & 1) == 0) {
        func_ov002_0220a568((char *) ((char *) param + 0x4234));
        func_ov002_02208098(param, 0x12);
        func_ov112_0229f784(param);
    } else {
        func_ov112_0229f92c(param);
    }
}
