/* letter_write_scene_8: 11 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_022a09f4 @ 0x022a09f4, 0xdc bytes, Thumb
 * func_ov122_022a099c @ 0x022a099c, 0x58 bytes, Thumb
 * func_ov122_022a0974 @ 0x022a0974, 0x28 bytes, Thumb
 * func_ov122_022a0928 @ 0x022a0928, 0x4c bytes, Thumb
 * func_ov122_022a0848 @ 0x022a0848, 0xe0 bytes, Thumb
 * func_ov122_022a07d4 @ 0x022a07d4, 0x74 bytes, Thumb
 * func_ov122_022a07a4 @ 0x022a07a4, 0x30 bytes, Thumb
 * func_ov122_022a0774 @ 0x022a0774, 0x30 bytes, Thumb
 * func_ov122_022a0750 @ 0x022a0750, 0x24 bytes, Thumb
 * func_ov122_022a0714 @ 0x022a0714, 0x3c bytes, Thumb
 * func_ov122_022a06e8 @ 0x022a06e8, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022a0928 {
    char pad_00[0xb4];
    unsigned char unk_B4;
    char pad_B5[0x0b];
    char unk_C0;
} UnkStruct_022a0928;

struct UnkStruct_022a0848 {
    u8 pad_00[0x9c];
    u32 unk_9C;
    u32 unk_A0;
    u8 pad_A4[8];
    u8 unk_AC;
    u8 unk_AD;
    u8 unk_AE;
};

typedef struct {
    unsigned char pad_00[0xAC];
    unsigned char unk_AC;
    unsigned char unk_AD;
    unsigned char unk_AE;
} UnkStruct_022a07d4;

typedef struct {
    char pad_00[0xb4];
    unsigned char b4;
} UnkStruct_022a0774;

extern int func_0208e484(void *p);
extern int func_ov095_02299a00(void *p);
extern int func_ov095_0229c448(void *p, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void *receiver);
extern int func_ov122_0229f958(void *self);
extern void func_ov122_0229f940(void *self);
extern void func_ov122_022a15b8(void *self, int a, int b);
extern void func_ov122_0229efd8(void *self, int a);
extern int func_ov122_022a0be4(void *self, int n);
extern void func_ov095_0229bf3c(void *p);
extern void func_ov095_0229c8e4(void *p, int a);
extern void func_ov095_0229cce0(void *p);
extern void func_ov122_0229f170(void *self);
extern unsigned short data_021fbe40;
extern int func_ov095_0229bf0c(void *);
extern int func_ov095_0229c548(void *);
extern void func_ov122_0229f150(void *);
extern int func_ov122_0229efe8(void *self, int value);
extern void func_ov122_0229f1b4(void *self);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(struct UnkStruct_022a0848 *self);
extern int func_ov122_0229f684(struct UnkStruct_022a0848 *self, int a, int b);
extern void func_ov122_0229f9a8(struct UnkStruct_022a0848 *self);
extern void func_ov122_022a14c0(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a0168(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a0204(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a0098(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a00fc(struct UnkStruct_022a0848 *self);
extern int func_ov122_022a006c(struct UnkStruct_022a0848 *self);
extern unsigned char *func_ov122_022a0054(struct UnkStruct_022a0848 *self);
extern void func_0200467c(int cmd);
extern void func_ov122_0229efc8(UnkStruct_022a07d4 *p, int a);
extern int func_0208e930(void *);
extern int func_ov002_0220a568(unsigned int);
extern void func_ov122_0229fc2c(void *receiver);
extern void func_ov122_0229f488(unsigned int);

void func_ov122_022a09f4(char *self)
{
    int a;
    int n;
    int m;

    if (func_0208e484(self + 0x4058) != 0) {
        a = func_ov095_02299a00(self + 0xc0);
        n = func_ov095_0229c448(self + 0xc0, a, 9);
        if (n == 0x112) {
            func_ov002_02208098((void *) (self), 0x10);
            func_ov002_0220a574(self + 0x4010);
            func_ov002_0220a4bc((void *) ((char *) self + 0x4010));
            if (func_ov122_0229f958(self) != 0) {
                func_ov122_0229f940(self);
                func_ov122_022a15b8(self, 1, 1);
            } else {
                func_ov122_0229f940(self);
            }
            func_ov122_0229efd8(self, 0x200);
        } else {
            m = func_ov122_022a0be4(self, n);
            if (m == 1 && ((*(u16 *) &data_021fbe40) & 1) != 0) {
                func_ov095_0229bf3c(self + 0xc0);
                func_ov002_02208098((void *) (self), 9);
                func_ov095_0229c8e4(self + 0xc0, a);
            } else if (m != 3) {
                if (m == 4) {
                    func_ov095_0229cce0(self + 0xc0);
                } else {
                    func_ov122_0229f170(self);
                }
            }
        }
    }
}

void func_ov122_022a099c(void *arg)
{
    int a;

    if ((data_021fbe40 & 1) == 0) {
        func_ov122_0229f170(arg);
        return;
    }
    if (func_ov095_0229bf0c((char *) arg + 0xc0) != 0) {
        a = func_ov095_0229c548((char *) arg + 0xc0);
        func_ov122_022a0be4(arg, func_ov095_0229c448((char *) arg + 0xc0, a, 9));
        func_ov095_0229c8e4((char *) arg + 0xc0, a);
    }
}

void func_ov122_022a0974(void *arg)
{
    if (func_0208e484((char *) arg + 0x4058)) {
        func_ov122_0229f150(arg);
        func_ov002_02208098((void *) (arg), 6);
    }
}

void func_ov122_022a0928(UnkStruct_022a0928 *self)
{
    if ((data_021fbe40 & 2) == 0) {
        func_ov002_02208098((void *) (self), self->unk_B4);
    } else {
        if (func_ov095_0229bf0c(&self->unk_C0) != 0) {
            func_ov122_022a0be4(self, 0x100);
            if (func_ov122_0229efe8(self, 0x100) != 0) {
                func_ov122_0229f1b4(self);
            }
        }
    }
}

void func_ov122_022a0848(struct UnkStruct_022a0848 *self)
{
    int t;
    u32 r4;
    u32 r6;

    if (func_ov002_02208014(self) != 0) {
        func_ov122_022a0054(self);
        return;
    }

    t = func_ov002_02208008(self);
    if (func_ov122_0229f684(self, t, 1) != 0) {
        func_ov122_0229f940((void *) self);
        func_ov122_0229f9a8(self);
        func_ov122_0229f1b4((void *) self);
        func_ov122_022a14c0(self);
        func_0200467c(0xb);
        return;
    }

    if (func_ov122_022a0168(self) != 0) {
        return;
    }

    r4 = self->unk_9C;
    r6 = self->unk_A0;

    if (func_ov122_022a0204(self) != 0) {
        if ((r4 != self->unk_9C) || (r6 != self->unk_A0)) {
            func_ov122_0229f1b4((void *) self);
        }
        return;
    }

    if (((*(struct { u16 _pad0; u16 flags; } *) &data_021fbe40).flags & 1) != 0) {
        func_ov002_02208098((void *) (self), 0xd);
        func_ov122_0229efd8((void *) self, 8);
        self->unk_AD = self->unk_AC;
        self->unk_AE = self->unk_AC;
    }

    if (func_ov122_022a0098(self) != 0) {
        return;
    }
    if (func_ov122_022a00fc(self) != 0) {
        return;
    }
    if (func_ov122_022a006c(self) != 0) {
        return;
    }
}

void func_ov122_022a07d4(UnkStruct_022a07d4 *param)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov002_02208098((void *) (param), 0xc);
        if (param->unk_AD == param->unk_AE) {
            func_ov122_0229efc8(param, 8);
        }
    } else {
        int ret = func_ov002_02208008((struct UnkStruct_022a0848 *) param);
        if (func_ov122_0229f684((struct UnkStruct_022a0848 *) param, ret, 0) != 0) {
            param->unk_AE = param->unk_AC;
            func_ov122_022a15b8((void *) param, 0, 1);
            func_ov122_0229f9a8((struct UnkStruct_022a0848 *) param);
            func_ov122_0229f1b4((void *) param);
            func_0200467c(0x15);
        }
    }
}

void func_ov122_022a07a4(void *p)
{
    if ((data_021fbe40 & 0x200) != 0) {
        return;
    }
    func_ov002_02208098((void *) (p), ((unsigned char *) p)[0xb4]);
    func_ov122_022a14c0((struct UnkStruct_022a0848 *) p);
}

void func_ov122_022a0774(UnkStruct_022a0774 *obj)
{
    int masked = data_021fbe40 & 0x100;
    if (masked != 0) {
        return;
    }
    func_ov002_02208098((void *) (obj), obj->b4);
    func_ov122_022a14c0((struct UnkStruct_022a0848 *) obj);
}

void func_ov122_022a0750(void *arg0)
{
    if (func_0208e930((char *) arg0 + 0x4010)) {
        func_ov002_02208098((void *) (arg0), 0x11);
    }
}

void func_ov122_022a0714(unsigned int param)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov002_0220a568(param + 0x4010);
        func_ov002_02208098((void *) (param), 0x12);
        func_ov122_0229fc2c((void *) param);
    } else {
        func_ov122_0229f488(param);
    }
}

void func_ov122_022a06e8(void *param)
{
    if (func_0208e930((char *) param + 0x4010)) {
        func_ov122_0229f170(param);
        func_ov122_0229efc8((UnkStruct_022a07d4 *) param, 0x200);
    }
}
