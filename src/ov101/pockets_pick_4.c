/* pockets_pick_4: 8 functions, module ov101
 * mwccarm 1.2/base -O4,s
 * func_ov101_0229d704 @ 0x0229d704, 0x1c bytes, Thumb
 * func_ov101_0229d6bc @ 0x0229d6bc, 0x48 bytes, Thumb
 * func_ov101_0229d624 @ 0x0229d624, 0x98 bytes, Thumb
 * func_ov101_0229d5a8 @ 0x0229d5a8, 0x7c bytes, Thumb
 * func_ov101_0229d4b4 @ 0x0229d4b4, 0xf4 bytes, Thumb
 * func_ov101_0229d410 @ 0x0229d410, 0xa4 bytes, Thumb
 * func_ov101_0229d398 @ 0x0229d398, 0x78 bytes, Thumb
 * func_ov101_0229d34c @ 0x0229d34c, 0x4c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229d4b4 {
    char pad_00[0xb3];
    unsigned char unk_B3;
    char pad_B4[0x21b4 - 0xb4];
    unsigned int unk_21B4;
    char pad_21B8[0x2810 - 0x21b8];
    unsigned int unk_2810;
};

extern unsigned char data_021fbdd8;
extern void func_ov101_0229c42c(void *self, unsigned char a, int b);
extern int func_ov002_02207cc0(int);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov002_02208e28(unsigned char *);
extern int func_ov002_02208054(unsigned char *, int);
extern void func_ov101_0229c51c(unsigned char *);
extern int func_ov002_02208b00(unsigned char *, unsigned char, unsigned char);
extern void func_ov002_02209114(unsigned char *, int, int);
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov101_0229ca2c(u8 *);
extern void func_ov101_0229cb44(u8 *);
extern int func_ov101_0229cdd0(u8 *, int, int, int);
extern int func_ov101_0229cd80(u8 *, int);
extern void func_ov101_0229ce50(u8 *, u8, int);
extern void func_ov101_0229cf80(u8 *);
extern void func_ov101_0229cb18(u8 *, int arg1);
extern unsigned short data_021fbe40[2];
extern int func_ov002_02208014(void *receiver);
extern void func_ov101_0229cfd4(void *self);
extern int func_ov002_02208008(void *self);
extern int func_ov101_0229c2c0(void *self, int arg);
extern void func_ov101_0229ca58(void *self);
extern void func_ov101_0229c7d0(void *self);
extern int func_ov002_02207d24(void *p, int v);
extern int func_ov101_0229cc50(void *self, unsigned char b);
extern int func_ov101_0229ce38(void *self, unsigned char b);
extern int func_ov101_0229cc20(void *self, unsigned char b);
extern void func_ov101_0229c660(void *self);
extern void func_ov101_0229c844(void *self);
extern void *func_ov002_0220a720(void *p, int v);
extern void func_0200467c(int cmd);
extern void func_ov002_02207d00(void *p);
extern void func_ov101_0229c624(void *self, unsigned char byte);
extern void func_ov101_0229c5dc(void *self, unsigned char byte);
extern void func_ov101_0229ca00(void *self);
extern int func_ov002_02209044(void *a, int b, void *c, int d);
extern void func_ov002_0220a1dc(void *a);
extern void func_ov101_0229c780(void *self);
extern void func_ov101_0229c720(void *self);
extern int func_0208e484(void *);

void func_ov101_0229d704(int arg)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) arg, 4);
    }
}

void func_ov101_0229d6bc(void *self)
{
    if (func_ov002_02207cc0((int) (char *) self + 0x21b4)) {
        if (*(unsigned char *) ((char *) self + 0xb9)) {
            (*(unsigned char *) ((char *) self + 0xb9))--;
        } else {
            func_ov101_0229c42c(self, *(unsigned char *) ((char *) self + 0xb0), 1);
            func_ov002_02208098(self, 2);
        }
    }
}

void func_ov101_0229d624(unsigned char *p)
{
    int flag;
    int result;
    unsigned char *q;

    if (func_ov002_02208e28(p + 0x2300) == 0) {
        return;
    }
    if (func_ov002_02208054(p, 1) != 0) {
        func_ov101_0229c51c(p);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag != 0) {
        result = func_ov002_02208b00(p + 0x2300, data_021f6c58, data_021f6c54);
        if (result < 0) {
            return;
        }
        func_ov002_02209114(p + 0x2300, result, 1);
        q = p + result;
        p[0xb7] = q[0x26ed];
        func_ov002_02208098((void *) p, 0x14);
    }
}

void func_ov101_0229d5a8(u8 *self)
{
    int x;

    func_ov101_0229ca2c(self);
    func_ov101_0229cb44(self);
    x = func_ov101_0229cdd0(self, *(unsigned int *) (self + 0xa4) + 8, *(unsigned int *) (self + 0xa8) + 8, 0);

    if (x == 0x10) {
        goto x_eq;
    }

    if ((*(u8 *) &data_021fbdd8) != 0) {
        goto flag_nonzero;
    }

    if (func_ov101_0229cd80(self, x) == 0) {
        func_ov101_0229ce50(self, self[0xb2], 4);
    }
    func_ov101_0229cf80(self);
    return;

flag_nonzero:
    func_ov101_0229cb18(self, x);
    return;

x_eq:
    if ((*(u8 *) &data_021fbdd8) != 0) {
        return;
    }
    func_ov101_0229ce50(self, self[0xb2], 4);
}

void func_ov101_0229d4b4(struct UnkStruct_0229d4b4 *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov101_0229cfd4(self);
        func_ov002_02207d24(&self->unk_21B4, 1);
        return;
    }

    {
        int arg = func_ov002_02208008(self);
        if (func_ov101_0229c2c0(self, arg) != 0) {
            func_ov101_0229ca58(self);
            func_ov101_0229c7d0(self);
            func_ov002_02207d24(&self->unk_21B4, 0);
            return;
        }

        if (func_ov101_0229cc50(self, self->unk_B3) == 0 && (data_021fbe40[1] & 1) != 0) {
            if (func_ov101_0229ce38(self, self->unk_B3) != 0) {
                if (func_ov101_0229cc20(self, self->unk_B3) == 0) {
                    func_ov101_0229c42c(self, self->unk_B3, 0);
                    return;
                } else {
                    return;
                }
            } else {
                if (self->unk_B3 == 0xf) {
                    func_ov101_0229c660(self);
                    return;
                } else {
                    return;
                }
            }
        } else {
            if ((data_021fbe40[1] & 2) != 0) {
                func_ov101_0229c844(self);
                func_ov002_0220a720(&self->unk_2810, 9);
                func_ov002_02208098(self, 0x17);
                func_0200467c(0x28);
                func_ov002_02207d24(&self->unk_21B4, 0);
                return;
            } else {
                func_ov002_02207d00(&self->unk_21B4);
                return;
            }
        }
    }
}

void func_ov101_0229d410(void *self)
{
    unsigned short flags;

    if (func_ov101_0229c2c0(self, func_ov002_02208008(self)) != 0) {
        func_ov101_0229ca58(self);
        func_ov101_0229c7d0(self);
        func_ov002_02207d24((char *) self + 0x21b4, 0);
        return;
    }

    flags = data_021fbe40[1];

    if (flags & 1) {
        if (func_ov101_0229ce38(self, *((unsigned char *) self + 0xb3)) != 0) {
            if (func_ov101_0229cc20(self, *((unsigned char *) self + 0xb3)) != 0) {
                func_ov101_0229c624(self, *((unsigned char *) self + 0xb3));
            } else {
                func_ov101_0229c5dc(self, *((unsigned char *) self + 0xb3));
            }
        } else {
            return;
        }
    } else if (flags & 2) {
        func_ov101_0229c624(self, *((unsigned char *) self + 0xb2));
    } else {
        func_ov101_0229ca00(self);
        func_ov002_02207d00((char *) self + 0x21b4);
    }
}

void func_ov101_0229d398(void *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov101_0229c51c((unsigned char *) self);
        return;
    }
    {
        int res = func_ov002_02208008(self);
        if (func_ov002_02209044((char *) self + 0x2300, res, (char *) self + 0xb8, 0) != 0) {
            func_ov101_0229c780(self);
            return;
        }
    }
    {
        unsigned short flags = (*(struct {
                                   unsigned short unk0;
                                   unsigned short unk2;
                               } *) data_021fbe40)
                                   .unk2;
        if (flags & 1) {
            func_ov002_0220a1dc((char *) self + 0x229c);
            func_ov002_02208098(self, 9);
            return;
        }
        if (flags & 2) {
            func_ov101_0229c720(self);
        }
    }
}

void func_ov101_0229d34c(unsigned char *p)
{
    if (func_0208e484(p + 0x229c)) {
        func_ov002_02209114((unsigned char *) (p + 0x2300), (unsigned char) p[0xb8], 1);
        p[0xb7] = *(p + p[0xb8] + 0x26ed);
        func_ov002_02208098(p, 0x14);
    }
}
