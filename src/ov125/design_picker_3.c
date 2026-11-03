/* design_picker_3: 12 functions, module ov125
 * mwccarm 1.2/base -O4,s
 * func_ov125_022a04c0 @ 0x022a04c0, 0x8 bytes, Thumb
 * func_ov125_022a04a0 @ 0x022a04a0, 0x20 bytes, Thumb
 * func_ov125_022a0474 @ 0x022a0474, 0x2c bytes, Thumb
 * func_ov125_022a0428 @ 0x022a0428, 0x4c bytes, Thumb
 * func_ov125_022a0418 @ 0x022a0418, 0x10 bytes, Thumb
 * func_ov125_022a0358 @ 0x022a0358, 0xc0 bytes, Thumb
 * func_ov125_022a0334 @ 0x022a0334, 0x24 bytes, Thumb
 * func_ov125_022a02b4 @ 0x022a02b4, 0x80 bytes, Thumb
 * func_ov125_022a0214 @ 0x022a0214, 0xa0 bytes, Thumb
 * func_ov125_022a012c @ 0x022a012c, 0xe8 bytes, Thumb
 * func_ov125_022a00ac @ 0x022a00ac, 0x80 bytes, Thumb
 * func_ov125_022a0060 @ 0x022a0060, 0x4c bytes, Thumb
 */

#include "types.h"

struct MyObj {
    u8 data[0x880];
};

typedef struct UnkStruct_022a012c {
    u8 pad_00[0x87b];
    u8 unk_87B;
    u8 unk_87C;
} UnkStruct_022a012c;

typedef struct GlobalReg {
    u16 pad_00;
    u16 flags;
} GlobalReg;

struct Flags {
    char pad_00[2];
    unsigned short flag;
};

extern void func_ov002_0220af74(void *);
extern void func_ov124_0229eea0(void *);
extern void func_ov002_022091cc(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov125_0229fd3c(void *);
extern void func_02001c08(unsigned char value);
extern void func_020029e8(int layer, int priority);
extern void func_020028bc(unsigned int mode, int a, int b, int c);
extern void func_ov124_0229f398(void *ptr, int a, int b);
extern void *func_020e9958(void *, int);
extern void func_020e993c(void *, void *);
extern void *func_020984e8(void);
extern void *func_020996b8(void *);
extern void *func_02072bb0(void *, int);
extern void *func_02072da0(void *);
extern void *func_02072d4c(void *);
extern void *func_02072f88(void *);
extern void func_020025c4(void *, void *, int, int, int);
extern int func_02002a88(void *, int, int, int, int);
extern int func_02002bd0(void *, int, int, int, int);
extern void MIi_CpuCopy16(const void *, void *, unsigned int);
extern void *data_021fbe94;
extern void func_ov124_0229ef4c(void *, int);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_02208054(unsigned char *self, int a);
extern void func_ov125_0229feb8(unsigned char *self);
extern int func_ov125_0229fdc4(unsigned char *self);
extern void *func_ov002_0220a720(unsigned char *p, int a);
extern void func_ov125_0229fc90(unsigned char *self);
extern void func_ov125_0229fc24(unsigned char *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern void func_ov125_0229f948(void *a);
extern unsigned char *func_ov002_02208098(void *a, unsigned char value);
extern int func_ov002_02208b00(void *a, u8 b, u8 c);
extern void func_ov002_02209114(void *a, int b, int c);
extern u8 func_ov125_0229fc84(void *a, int b);
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern volatile GlobalReg data_021fbe40; // placed at 0x021fbe40
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_022a012c *self);
extern int func_ov125_0229f784(UnkStruct_022a012c *self, int arg);
extern void func_ov125_0229fee4(UnkStruct_022a012c *self);
extern void func_ov125_0229fd04(UnkStruct_022a012c *self);
extern void func_ov125_0229fa80(UnkStruct_022a012c *self);
extern void func_ov125_0229faf8(UnkStruct_022a012c *self);
extern int func_ov002_02207d24(void *addr, int arg);
extern void func_ov002_02207d00(void *addr);
extern void func_ov002_0220a1dc(void *addr);
extern int func_ov002_02209044(void *a, int b, void *c, int d);
void func_ov125_0229fa2c(void *self);
void func_ov125_0229f9c8(void *self);
extern int func_0208e484(void *ptr);

void func_ov125_022a0474(void *arg0);

void func_ov125_022a04c0(void *arg0)
{
    func_ov125_022a0474((void *) arg0);
}

void func_ov125_022a04a0(void *arg0)
{
    func_ov002_0220af74((char *) arg0 + 0x6a8);
    func_ov124_0229eea0((char *) arg0 + 0x94);
}

void func_ov125_022a0474(void *arg0)
{
    func_ov002_022091cc((char *) arg0 + 0x180);
    if (func_ov002_02207d5c((char *) arg0 + 0x574)) {
        func_ov125_0229fd3c(arg0);
    }
}

void func_ov125_022a0428(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 1);
    func_020028bc(3, 0, 0, 0);
}

void func_ov125_022a0418(void *ptr)
{
    func_ov124_0229f398((char *) ptr + 0x94, 6, 4);
}

void func_ov125_022a0358(void)
{
    void *dev;
    void *buf;
    void *buf2;
    void *h;
    unsigned char i;
    int off;

    dev = data_021fbe94;
    buf = func_020e9958(dev, 0x1000);
    h = func_020996b8(func_020984e8());
    for (i = 0; i < 8; i++) {
        func_020025c4(func_02072da0(func_02072bb0(h, i)), buf, i * 4, 4, 4);
    }
    func_02002a88(buf, 8, 0xc0, 0xc0, 0x13f);
    func_020e993c(dev, buf);

    buf2 = func_020e9958(dev, 0x100);
    off = 0;
    for (i = 0; i < 8; i++) {
        MIi_CpuCopy16(func_02072f88(func_02072d4c(func_02072bb0(h, i))), (unsigned short *) buf2 + off, 0x20);
        off += 0x10;
    }
    func_02002bd0(buf2, 8, 5, 5, 0xc);
    func_020e993c(dev, buf2);
}

void func_ov125_022a0334(void *self)
{
    func_ov125_022a0358();
    func_ov124_0229ef4c((char *) self + 0x94, 4);
    func_ov002_0220af94((void *) ((char *) self + 0x6a8));
}

void func_ov125_022a02b4(unsigned char *self)
{
    unsigned int flag;
    int n;

    if (func_ov002_02208054(self, 1)) {
        func_ov125_0229feb8(self);
        return;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag > 0) {
        n = func_ov125_0229fdc4(self);
        if (n == 8) {
            func_ov002_0220a720(self + 0x6a8, 9);
            func_ov002_02208098((void *) self, 10);
        } else if (n != 9) {
            func_ov125_0229fc90(self);
            self[0x87b] = (unsigned char) n;
            func_ov125_0229fc24(self);
        }
    }
}

void func_ov125_022a0214(struct MyObj *obj)
{
    if (func_ov002_02208054((unsigned char *) obj, 1) != 0) {
        func_ov125_0229f948(obj);
        func_ov002_02208098(obj, 3);
        obj->data[0x87c] = obj->data[0x87b];
    } else {
        unsigned int flag = ((*(u8 *) &data_021fbdd8) != 0 && (*(u8 *) &data_021fbddc) != 0);
        if (flag != 0) {
            int idx = func_ov002_02208b00(&obj->data[0x180], data_021f6c58, data_021f6c54);
            if (idx >= 0) {
                func_ov002_02209114(&obj->data[0x180], idx, 1);
                obj->data[0x87d] = func_ov125_0229fc84(obj, idx);
                func_ov002_02208098(obj, 8);
            }
        }
    }
}

void func_ov125_022a012c(UnkStruct_022a012c *self)
{
    u16 reg;

    if (func_ov002_02208014(self)) {
        func_ov125_0229fee4(self);
        func_ov002_02207d24((char *) self + 0x574, 1);
        return;
    }

    if (func_ov125_0229f784(self, func_ov002_02208008(self))) {
        func_ov125_0229fd04(self);
        func_ov125_0229fa80(self);
        func_ov002_02207d24((char *) self + 0x574, 0);
        return;
    }

    reg = data_021fbe40.flags;

    if (reg & 1) {
        if (self->unk_87C == 8) {
            func_ov002_0220a1dc((char *) self + 0x644);
            func_ov002_02208098((void *) self, 6);
            return;
        } else {
            func_ov002_02207d24((char *) self + 0x574, 1);
            func_ov125_0229fc90((unsigned char *) self);
            self->unk_87B = self->unk_87C;
            func_ov125_0229fc24((unsigned char *) self);
            func_ov125_0229faf8(self);
            return;
        }
    } else if (reg & 2) {
        func_ov125_0229faf8(self);
        func_ov002_0220a720((unsigned char *) ((char *) self + 0x6a8), 9);
        func_ov002_02208098((void *) self, 10);
        func_ov002_02207d24((char *) self + 0x574, 1);
        return;
    } else {
        func_ov002_02207d00((char *) self + 0x574);
        return;
    }
}

void func_ov125_022a00ac(void *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov125_0229faf8((UnkStruct_022a012c *) self);
        func_ov002_02208098(self, 1);
    } else {
        int val = func_ov002_02208008((UnkStruct_022a012c *) self);
        if (func_ov002_02209044((char *) self + 0x180, val, (char *) self + 0x87e, 0) != 0) {
            func_ov125_0229fa2c(self);
        }
        if (((*(struct Flags *) &data_021fbe40).flag & 1) != 0) {
            func_ov002_0220a1dc((char *) self + 0x644);
            func_ov002_02208098(self, 4);
        } else {
            if (((*(struct Flags *) &data_021fbe40).flag & 2) != 0) {
                func_ov125_0229f9c8(self);
            }
        }
    }
}

void func_ov125_022a0060(unsigned char *p)
{
    if (func_0208e484(p + 0x644)) {
        func_ov002_02209114(p + 0x180, (unsigned char) (*(p + 0x87e)), 1);
        *(p + 0x87d) = (unsigned char) func_ov125_0229fc84(p, (unsigned char) (*(p + 0x87e)));
        func_ov002_02208098(p, 8);
    }
}
