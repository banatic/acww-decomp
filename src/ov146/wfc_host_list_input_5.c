/* wfc_host_list_input_5: 6 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229a9b8 @ 0x0229a9b8, 0x110 bytes, Thumb
 * func_ov146_0229a984 @ 0x0229a984, 0x34 bytes, Thumb
 * func_ov146_0229a950 @ 0x0229a950, 0x34 bytes, Thumb
 * func_ov146_0229a8ec @ 0x0229a8ec, 0x64 bytes, Thumb
 * func_ov146_0229a89c @ 0x0229a89c, 0x50 bytes, Thumb
 * func_ov146_0229a858 @ 0x0229a858, 0x44 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a9b8 {
    char pad_00[0xa8];
    int unk_A8;
    char pad_AC[0xae - 0xac];
    s16 unk_AE;
    u8 unk_B0;
    char pad_B1[0xbb - 0xb1];
    u8 unk_BB;
};

extern int func_ov002_02208054(struct UnkStruct_0229a9b8 *self, int a);
extern void func_ov146_0229a744(struct UnkStruct_0229a9b8 *self);
extern void func_ov146_0229a6a4(struct UnkStruct_0229a9b8 *self);
extern void func_ov146_0229a6dc(struct UnkStruct_0229a9b8 *self);
extern int func_ov146_02299e9c(struct UnkStruct_0229a9b8 *self, int b);
extern void func_0200467c(int cmd);
extern int func_ov146_02299cbc(struct UnkStruct_0229a9b8 *self, int a, int b);
extern void func_ov002_0220a574(void *p);
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern unsigned char data_021fbdd8; // 0x021fbdd8
extern unsigned char data_021f6c54; // 0x021f6c54
extern void func_ov146_02299c44(int, int, int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);
extern void func_ov146_02299c34(void *arg0);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *obj);
extern int func_ov146_0229985c(void *obj, int arg);
extern void func_ov146_0229a760(void *obj);
extern void func_ov146_0229a534(void *obj);
extern void func_ov146_0229a490(void *obj);
extern void func_ov146_0229a578(void *obj);
extern struct {
    unsigned char pad[2];
    unsigned short flags;
} data_021fbe40;
extern void func_ov146_02299ba8(void *arg0);
extern int func_ov146_0229a5e8(void *self);
extern int func_ov146_0229a59c(void *self);
extern void func_ov002_0220a0b4(void *self, int a, int b);
extern int func_ov146_02299b80(const void *p);
extern void func_ov146_0229a464(void *p);

void func_ov146_0229a9b8(struct UnkStruct_0229a9b8 *self)
{
    int r4;
    int r6;
    int cond;
    int idx;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov146_0229a744(self);
        return;
    }

    cond = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0);
    if (cond == 0) {
        return;
    }

    r4 = data_021f6c58;
    r6 = (*(u8 *) &data_021f6c54);

    if (r6 >= 0xa9 && r6 <= 0xbc) {
        if (r4 >= 0x39) {
            if (r4 < 0x75) {
                func_ov146_0229a6a4(self);
                return;
            }

            if (r4 >= 0x8b && r4 < 0xc7) {
                if (self->unk_B0 == 8) {
                    func_ov146_0229a6dc(self);
                    return;
                }
            }
        }
    }

    if (r4 >= 0x18 && r4 <= 0xe0 && r6 >= 0x38 && r6 < 0x98) {
        idx = self->unk_AE + ((r6 - (0x38 - (self->unk_A8 & 0xf))) >> 4);
        if (idx < 0x20) {
            r4 = *(u8 *) ((char *) self + idx + 0xea);
            if (func_ov146_02299e9c(self, r4) != 0) {
                if (self->unk_BB != r4) {
                    self->unk_BB = r4;
                    func_0200467c(0x29);
                }
            }
        }
        return;
    }

    if (func_ov146_02299cbc(self, r4, r6) != 0) {
        func_ov002_02208098((int) self, 1);
        return;
    }

    if (r4 >= 0xe6 && r4 <= 0xee && r6 >= 0x38 && r6 <= 0x88) {
        func_ov002_0220a574((char *) self + 0x1fb4);
        func_ov002_02208098((int) self, 2);
    }
}

void func_ov146_0229a984(int arg)
{
    if (data_021fbdd8) {
        func_ov146_02299c44(arg, data_021f6c54, 0);
    } else {
        func_ov146_02299c34((void *) arg);
        func_ov002_02208098(arg, 0);
    }
}

void func_ov146_0229a950(int param)
{
    if (data_021fbdd8 != 0) {
        func_ov146_02299c44(param, data_021f6c54, 1);
    } else {
        func_ov146_02299c34((void *) param);
        func_ov002_02208098(param, 0);
    }
}

void func_ov146_0229a8ec(void *obj)
{
    if (func_ov002_02208014(obj)) {
        func_ov146_0229a760(obj);
        return;
    }
    if (func_ov146_0229985c(obj, func_ov002_02208008(obj))) {
        func_ov146_0229a534(obj);
        return;
    }
    {
        unsigned short f = data_021fbe40.flags;
        if ((f & 1) != 0) {
            func_ov146_0229a490(obj);
            return;
        } else if ((f & 2) != 0) {
            func_ov146_0229a578(obj);
            func_ov146_0229a6a4((struct UnkStruct_0229a9b8 *) obj);
            return;
        }
    }
}

void func_ov146_0229a89c(void *self)
{
    if (((*(unsigned short *) &data_021fbe40) & 1) != 0) {
        func_ov146_02299ba8((void *) self);
        func_ov002_0220a0b4((char *) self + 0x15cc, func_ov146_0229a5e8(self), func_ov146_0229a59c(self));
    } else {
        func_ov146_02299c34(self);
        func_ov002_02208098((int) self, 5);
    }
}

void func_ov146_0229a858(void *p)
{
    int a;
    int b;

    if (func_ov146_02299b80(p) != 0) {
        func_ov002_02208098((int) p, 3);
        func_ov146_0229a464(p);
    }

    a = func_ov146_0229a5e8((void *) p);
    b = func_ov146_0229a59c((void *) p);
    func_ov002_0220a0b4((char *) p + 0x15cc, a, b);
}
