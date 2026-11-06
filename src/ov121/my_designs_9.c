/* my_designs_9: 6 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229b764 @ 0x0229b764, 0x70 bytes, Thumb
 * func_ov121_0229b6f0 @ 0x0229b6f0, 0x74 bytes, Thumb
 * func_ov121_0229b64c @ 0x0229b64c, 0xa4 bytes, Thumb
 * func_ov121_0229b574 @ 0x0229b574, 0xd8 bytes, Thumb
 * func_ov121_0229b484 @ 0x0229b484, 0xf0 bytes, Thumb
 * func_ov121_0229b40c @ 0x0229b40c, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xad];
    unsigned char unk_AD;
    unsigned char unk_AE;
    unsigned char unk_AF;
} UnkStruct_0229b6f0;

struct UnkStruct_0229b64c {
    u8 pad_00[0xAF];
    u8 unk_AF;
};

typedef struct {
    unsigned char pad_00[0xb1];
    unsigned char unk_B1;
    unsigned char pad_B2[0x226];
    unsigned int unk_2D8;
} Obj_ov121_0229c3a8;

extern int func_ov002_02208054(void *self, int a);
extern unsigned char *func_ov121_0229afd8(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov121_0229ae18(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov002_02207cf8(void *p);
extern void func_0200467c(int cmd);
extern void func_ov002_02207ce4(void *p, int a);
extern int func_ov121_0229ad68(void);
extern void func_ov121_02299a4c(void *s, int a);
extern int func_ov002_02207d24(void *p, int a);
extern void func_ov002_02207d00(void *p);
extern void func_ov121_02299a3c(struct UnkStruct_0229b64c *self, unsigned short mask);
extern int func_0206f56c(void);
extern void func_ov121_0229aec4(struct UnkStruct_0229b64c *self, int val);
extern int func_ov121_0229ac00(struct UnkStruct_0229b64c *self);
extern int func_ov121_0229add4(struct UnkStruct_0229b64c *self);
extern int func_ov002_02208b00(unsigned char *, unsigned char, unsigned char);
extern unsigned char func_ov121_0229ab80(unsigned char *, int);
extern void func_ov121_0229a53c(unsigned char *);
extern void func_ov121_0229a1e4(unsigned char *);
extern void func_ov002_02209114(unsigned char *, int, int);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208014(void *receiver);
extern unsigned char *func_ov121_0229b008(Obj_ov121_0229c3a8 *self);
extern int func_ov002_02208008(Obj_ov121_0229c3a8 *self);
extern int func_ov121_02299ccc(Obj_ov121_0229c3a8 *self, int a, int b);
extern void func_ov121_0229a450(Obj_ov121_0229c3a8 *self);
extern void func_ov121_0229a2e4(Obj_ov121_0229c3a8 *self);
extern int func_ov121_02299fc8(Obj_ov121_0229c3a8 *self);
extern void func_ov121_0229a170(Obj_ov121_0229c3a8 *self);
extern void func_ov121_0229a130(Obj_ov121_0229c3a8 *self);
extern int func_ov090_02299078(int arg);
extern int func_ov090_02299098(int arg);
extern int func_ov121_0229bc70(Obj_ov121_0229c3a8 *self, int arg);
extern unsigned short data_021fbe40[];
extern int func_ov121_0229adac(void *p, unsigned char c);
extern void func_ov121_0229a108(void *p);
extern void func_ov121_0229a0e0(void *p);

void func_ov121_0229b764(void *self)
{
    unsigned int cond;
    int r;

    if (func_ov002_02208054(self, 1)) {
        func_ov121_0229afd8(self);
        return;
    }
    if (data_021fbdd8 == 0) {
        goto zero;
    }
    if (data_021fbddc == 0) {
        goto zero;
    }
    cond = 1;
    goto done;
zero:
    cond = 0;
done:
    if (cond) {
        r = func_ov121_0229ae18(self);
        if (r == 0x18) {
            return;
        }
        func_ov002_02208098(self, 1);
        *((unsigned char *) self + 0xad) = r;
        func_ov002_02207cf8((unsigned char *) self + 0x2d8);
        func_0200467c(0xc);
    }
}

void func_ov121_0229b6f0(UnkStruct_0229b6f0 *s)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(s, 0);
        func_ov002_02207ce4((char *) s + 0x2d8, 0x3c);
    } else {
        if (func_ov121_0229ad68()) {
            s->unk_AE = s->unk_AD;
            func_ov121_02299a4c(s, 4);
            s->unk_AF = 0x18;
            func_ov002_02208098(s, 2);
            func_ov002_02207d24((char *) s + 0x2d8, 1);
            func_0200467c(0xd);
        } else {
            func_ov002_02207d00((char *) s + 0x2d8);
        }
    }
}

void func_ov121_0229b64c(struct UnkStruct_0229b64c *self)
{
    func_ov121_02299a3c(self, 8);
    if (func_0206f56c() != 0) {
        func_ov121_02299a3c(self, 4);
        func_ov121_0229aec4(self, 0x18);
        func_ov002_02208098((void *) self, 0);
    } else {
        if ((*(u8 *) &data_021fbdd8) == 0) {
            func_ov121_02299a3c(self, 4);
            func_ov121_0229aec4(self, 0x18);
            if (func_ov121_0229ac00(self) == 0) {
                func_ov002_02208098((void *) self, 0);
            }
        } else {
            self->unk_AF = (unsigned char) func_ov121_0229add4(self);
            if (self->unk_AF >= 9 && self->unk_AF <= 15) {
                func_ov121_0229aec4(self, self->unk_AF);
                func_ov121_02299a4c((void *) self, 8);
            } else {
                if (self->unk_AF <= 7 || self->unk_AF == 8) {
                    func_ov121_02299a4c((void *) self, 8);
                }
                func_ov121_0229aec4(self, 0x18);
            }
        }
    }
}

void func_ov121_0229b574(unsigned char *self)
{
    int ret, flag;
    unsigned char byte;

    if (func_0206f56c() != 0) {
        func_ov121_0229a53c(self);
        return;
    }

    if (func_ov002_02208054((void *) self, 1) != 0) {
        func_ov121_0229a1e4(self);
        func_ov002_02208098((void *) self, 0xc);
        self[0xb1] = self[0xaf];
        return;
    }

    {
        unsigned int cond = 0;
        if (data_021fbdd8 != 0 && data_021fbddc != 0) {
            cond = 1;
        }
        if (cond > 0) {
            ret = func_ov002_02208b00(self + 0x528, data_021f6c58, data_021f6c54);
            if (ret < 0) {
                return;
            }

            flag = 1;
            self[0xb2] = func_ov121_0229ab80(self, ret);
            byte = self[0xb2];

            switch (byte) {
                case 0:
                case 1:
                case 2:
                case 3:
                    func_0200467c(0x50);
                    break;
                case 4:
                case 5:
                    break;
                case 6:
                    flag = 0;
                    break;
            }

            func_ov002_02209114(self + 0x528, ret, flag);
            func_ov002_02208098((void *) self, 0xf);
        }
    }
}

void func_ov121_0229b484(Obj_ov121_0229c3a8 *self)
{
    unsigned short flags;

    if (func_ov002_02208014(self) != 0) {
        func_ov121_0229b008(self);
        func_ov002_02207d24(&self->unk_2D8, 1);
        return;
    } else {
        if (func_ov121_02299ccc(self, func_ov002_02208008(self), 0) != 0) {
            func_ov121_0229a450(self);
            func_ov121_0229a2e4(self);
            func_ov002_02207d24(&self->unk_2D8, 0);
            return;
        }

        if (((*(struct {
                 unsigned short pad;
                 unsigned short flags;
             } *) data_021fbe40)
                 .flags &
             1) != 0) {
            func_ov002_02207d24(&self->unk_2D8, 1);
            if (func_ov121_02299fc8(self) != (int) -1) {
                func_ov121_0229a170(self);
                return;
            }
            if (self->unk_B1 <= 7) {
                func_ov121_0229a130(self);
                return;
            }
        }

        flags = (*(struct {
                    unsigned short pad;
                    unsigned short flags;
                } *) data_021fbe40)
                    .flags;
        if ((flags & 0x100) != 0) {
            func_ov121_0229bc70(self, func_ov090_02299078(1));
            return;
        }
        if ((flags & 0x200) != 0) {
            func_ov121_0229bc70(self, func_ov090_02299098(1));
            return;
        }
        if ((flags & 2) != 0) {
            func_ov121_0229bc70(self, 7);
            return;
        }
        func_ov002_02207d00(&self->unk_2D8);
        return;
    }
}

void func_ov121_0229b40c(unsigned char *param)
{
    if (func_0206f56c() != 0) {
        func_ov121_02299a3c((struct UnkStruct_0229b64c *) param, 4);
        func_ov121_0229bc70((Obj_ov121_0229c3a8 *) param, 7);
    } else {
        int result = func_ov002_02208008((Obj_ov121_0229c3a8 *) param);
        if (func_ov121_02299ccc((Obj_ov121_0229c3a8 *) param, result, 1) != 0) {
            func_ov121_0229a2e4((Obj_ov121_0229c3a8 *) param);
        } else {
            if (data_021fbe40[1] & 1) {
                if (func_ov121_0229adac(param, param[0xb1]) == 0) {
                    func_ov121_0229a108(param);
                }
            }
            if (data_021fbe40[1] & 2) {
                func_ov121_0229a0e0(param);
            }
        }
    }
}
