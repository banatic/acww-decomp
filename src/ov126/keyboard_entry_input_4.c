/* keyboard_entry_input_4: 4 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a04e8 @ 0x022a04e8, 0x64 bytes, Thumb
 * func_ov126_022a03dc @ 0x022a03dc, 0x10c bytes, Thumb
 * func_ov126_022a032c @ 0x022a032c, 0xb0 bytes, Thumb
 * func_ov126_022a027c @ 0x022a027c, 0xb0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xa8];
    u8 a8;
    u8 a9;
    u8 aa;
    u8 pad_AB[0x19c - 0xab];
    u8 sub19c;
    u8 pad_19D[0x4248 - 0x19d];
    u16 unk_4248;
} UnkStruct_022a027c;

extern void func_ov095_0229cce0(void *p);
extern int func_ov095_0229c54c(void *p, unsigned char a, unsigned char b);
extern void *func_ov095_0229c448(void *p, int idx, int n);
extern void func_ov095_0229c8e4(void *p, int idx);
extern void func_ov095_0229bf3c(void *p);
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;
extern int func_ov095_0229ba44(void *p, int v, int n);
extern int func_ov095_0229bebc(void *p, int v);
extern void func_ov126_022a0168(void *p);
extern void func_ov126_022a0110(void *receiver);
extern void func_ov126_022a0614(void *p);
extern void func_ov126_022a054c(void *p);
extern void func_ov126_022a0ae0(void *p, int v);
extern int func_ov126_022a01dc(void *p, unsigned short v);
extern int func_ov126_022a0904(unsigned char *p);
extern int func_ov095_0229bb9c(void *receiver, int value);
extern int func_ov095_0229bb98(void *receiver, int value);
extern int func_ov095_0229bb94(void *receiver, int value);
extern int func_ov095_0229bba0(unsigned char *p1, unsigned char *p2, int val, int a4);
extern void func_ov126_022a08c4(unsigned char *p);
extern int func_ov126_022a0740(UnkStruct_022a027c *self);
extern void func_ov126_022a06d8(UnkStruct_022a027c *self);
extern void func_ov095_0229b3ec(const void *p);
extern int func_ov095_0229b3a0(const void *p, const void *q, int _x);
extern void func_0200467c(int cmd);

int func_ov126_022a03dc(unsigned char *self, int v);
int func_ov126_022a032c(unsigned char *self, int mode);
int func_ov126_022a027c(UnkStruct_022a027c *self, int b);

int func_ov126_022a04e8(void *self)
{
    int idx;
    int ret;
    func_ov095_0229cce0((char *) self + 0x19c);
    idx = func_ov095_0229c54c((char *) self + 0x19c, data_021f6c58, data_021f6c54);
    if (idx == -1) {
        return 0;
    }
    ret = func_ov126_022a03dc((unsigned char *) self, (int) (func_ov095_0229c448((char *) self + 0x19c, idx, 9)));
    func_ov095_0229c8e4((char *) self + 0x19c, idx);
    func_ov095_0229bf3c((char *) self + 0x19c);
    return ret;
}

int func_ov126_022a03dc(unsigned char *self, int v)
{
    int ret;
    int r6 = 1;

    ret = func_ov095_0229ba44(self + 0x19c, v, 6);
    if (ret != 0) {
        func_ov126_022a0168(self);
        return ret;
    }

    if (func_ov095_0229bebc(self + 0x19c, v) != 0) {
        switch (v) {
            case 0x100:
                func_ov126_022a027c((UnkStruct_022a027c *) self, r6);
                break;
            case 0x103:
            case 0x104:
            case 0x105:
                if (func_ov126_022a032c((unsigned char *) self, v) == 0) {
                    func_ov126_022a0110(self);
                }
                r6 = 2;
                break;
            case 0x118:
                func_ov126_022a0614(self);
                r6 = 2;
                break;
            case 0x119:
                func_ov126_022a054c(self);
                r6 = 2;
                break;
            case 0x116:
                func_ov126_022a0ae0(self, 0);
                r6 = 3;
                break;
            case 0x117:
                func_ov126_022a0ae0(self, r6);
                r6 = 3;
                break;
            default:
                r6 = 2;
                break;
        }
    } else {
        if (func_ov126_022a01dc(self, (unsigned short) v) == 0) {
            func_ov126_022a0110(self);
        }
    }

    return r6;
}

int func_ov126_022a032c(unsigned char *self, int mode)
{
    volatile int argument_values[2];
    int result;

    result = func_ov126_022a0904(self);
    if (!result) {
        return 0;
    }

    switch (mode) {
        case 0x103:
            result = func_ov095_0229bb9c(self + 0x19c, result);
            break;
        case 0x104:
            result = func_ov095_0229bb98(self + 0x19c, result);
            break;
        case 0x105:
            result = func_ov095_0229bb94(self + 0x19c, result);
            break;
    }

    if (!result) {
        return 0;
    }

    if (!(argument_values[0] = (int) (self[0xa6]), argument_values[1] = (int) (0x2710),
          func_ov095_0229bba0(self + 0x19c, self + 0x4248, result, self[0xa8]))) {
        return 0;
    }

    func_ov126_022a0168((void *) self);
    func_ov126_022a08c4(self);
    return 1;
}

int func_ov126_022a027c(UnkStruct_022a027c *self, int b)
{
    if (func_ov126_022a0740(self)) {
        func_ov095_0229b3ec(&self->sub19c);
        func_ov126_022a06d8(self);
    } else if (self->a8) {
        if (func_ov095_0229b3a0(&self->sub19c, &self->unk_4248, self->a8) == 0) {
            self->a9 = self->a8;
            self->aa = self->a8 - 1;
            func_ov126_022a06d8(self);
        }
    } else if (self->unk_4248) {
        self->a9 = 0;
        self->aa = 1;
        func_ov126_022a06d8(self);
    } else {
        if (b) {
            func_ov126_022a0110((void *) self);
        }
        return 0;
    }
    func_0200467c(0x35);
    func_ov126_022a0168((void *) self);
    func_ov126_022a08c4((unsigned char *) self);
    return 1;
}
