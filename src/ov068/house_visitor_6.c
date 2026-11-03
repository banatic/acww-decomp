/* house_visitor_6: 16 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02276520 @ 0x02276520, 0x44 bytes, Thumb
 * func_ov068_02276510 @ 0x02276510, 0x10 bytes, Thumb
 * func_ov068_022764b4 @ 0x022764b4, 0x5c bytes, Thumb
 * func_ov068_0227647c @ 0x0227647c, 0x38 bytes, Thumb
 * func_ov068_02276458 @ 0x02276458, 0x24 bytes, Thumb
 * func_ov068_022763e4 @ 0x022763e4, 0x72 bytes, Thumb
 * func_ov068_022763c8 @ 0x022763c8, 0x1a bytes, Thumb
 * func_ov068_02276394 @ 0x02276394, 0x34 bytes, Thumb
 * func_ov068_022762c0 @ 0x022762c0, 0xd4 bytes, Thumb
 * func_ov068_0227629c @ 0x0227629c, 0x22 bytes, Thumb
 * func_ov068_02276278 @ 0x02276278, 0x22 bytes, Thumb
 * func_ov068_02276254 @ 0x02276254, 0x22 bytes, Thumb
 * func_ov068_02276230 @ 0x02276230, 0x22 bytes, Thumb
 * func_ov068_0227620c @ 0x0227620c, 0x22 bytes, Thumb
 * func_ov068_022761f0 @ 0x022761f0, 0x1a bytes, Thumb
 * func_ov068_022761d0 @ 0x022761d0, 0x20 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_022764b4 {
    void *unk_00;
    u32 unk_04;
    u32 unk_08;
};

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0227647c;

typedef struct UnkStruct_022762c0 {
    u8 unk_00[0x560];
    u8 unk_560;
    u8 unk_561[0x898 - 0x560 - 1];
    u32 state;
    u8 buf_89c[0xa5e - 0x89c];
    u16 unk_A5E;
    u8 unk_A60;
} UnkStruct_022762c0;

typedef struct {
    char pad_00[0x1a4];
    int unk_1A4;
} UnkStruct_022761d0;

extern int func_0202e1dc(void *argument0);
extern int func_020984e8(void);
extern char *func_02099640(int argument0);
extern int func_0209bba0(char *p);
extern void func_0209bb90(char *p, int n);
extern int data_ov068_022788ec;
extern void func_ov068_02275b8c(void *argument0);
extern struct UnkStruct_022764b4 *data_021c80bc;
extern int func_02037e0c(void *, int, int, int);
extern int func_0204bc90(int tile);
extern void func_020308e0(int, int);
extern int func_02099870(int arg);
extern int func_020804b8(int arg1, int arg2);
extern void func_02081e14(int arg1, int arg2, int arg3, int arg4);
extern void func_0201af28(void *dst, int a, int b, int c, int d);
extern void func_0209e234(void *, int);
extern void func_0209e474(void *);
extern int func_0209e3ac(void *, void *, int);
extern void MI_CpuCopy8(void *, void *, u32);
extern int func_02014868(void *ptr);
extern int func_ov068_02275c78(UnkStruct_022762c0 *self, int mode);
extern int func_020644cc(int arg);
extern void func_0202dc3c(void *ptr, int value, int count);

void func_ov068_022761d0(UnkStruct_022761d0 *obj, int val);

int func_ov068_02276520(void *argument0)
{
    char *p;

    if (func_0202e1dc(argument0) == 0) {
        return 0;
    }

    p = func_02099640((int) func_020984e8()) + 0xa4;

    if (func_0209bba0(p + 0x10) == 1) {
        p += 0x10;
        func_0209bb90(p, 2);
    }

    data_ov068_022788ec = 0;
    return 1;
}

int func_ov068_02276510(void *argument0)
{
    func_ov068_02275b8c(argument0);
    return 1;
}

void func_ov068_022764b4(void *receiver)
{
    struct UnkStruct_022764b4 *q;
    void *base;
    int y;
    int x;
    int zero;
    int tile;

    zero = 0;
    q = data_021c80bc;
    if (q->unk_04 > zero && q->unk_08 > zero && q->unk_00 != 0) {
        base = q->unk_00;
    } else {
        base = 0;
    }
    for (y = 0; y < 0x10; y++) {
        for (x = 0; x < 0x10; x++) {
            if ((tile = func_02037e0c(base, x, y, zero)) != 0 && func_0204bc90(tile) != 0) {
                func_020308e0(x, y);
            }
        }
    }
}

void func_ov068_0227647c(UnkStruct_0227647c *param)
{
    int a;
    int b;
    int c;

    a = func_020984e8();
    if (a == 0) {
        return;
    }
    if (param->unk_830 == 0) {
        return;
    }
    b = func_02099870(a);
    c = func_020804b8(param->unk_830, b);
    func_02081e14(c, 0, 0, 0);
}

void func_ov068_02276458(void *p)
{
    func_0201af28((char *) p + 0x350, 1, 0x100, 0x19, 0x33);
}

int func_ov068_022763e4(void *arg0)
{
    u32 a[2];
    u32 b[2];
    u32 c[2];

    MI_CpuCopy8((u8 *) func_02099640((int) ((void *) func_020984e8())) + 0xc0, a, 8);
    MI_CpuCopy8(a, b, 8);
    func_0209e234(b, 0x1e);

    c[0] = 0;
    c[1] = 0;
    func_0209e474(c);

    if (func_0209e3ac(a, c, 0x3e) != -1) {
        if (func_0209e3ac(a, c, 0x3e) != 0) {
            goto fail;
        }
    }

    if (func_0209e3ac(c, b, 0x3e) != -1) {
        goto fail;
    }

    return 1;

fail:
    return 0;
}

void func_ov068_022763c8(void)
{
    func_0209bb90((char *) ((int) func_02099640(func_020984e8()) + 0xb4), 4);
}

int func_ov068_02276394(void *self)
{
    if (func_02014868((char *) self + 0x618) != 0) {
        return 0;
    }
    if (*(unsigned int *) ((char *) self + 0x898) - 5 <= 1) {
        return 1;
    }
    return 0;
}

void func_ov068_022762c0(UnkStruct_022762c0 *self, int type, unsigned char param)
{
    switch (type) {
        case 3:
            self->unk_560 = param;
            if (self->state == 0) {
                break;
            }
            if (self->state == 5) {
                self->unk_A5E = (u16) ((func_020644cc(0x28) + 0x3c) * 0x3c);
            }
            func_ov068_02275c78(self, 7);
            break;

        case 0:
            self->unk_560 = param;
            func_ov068_022761d0((UnkStruct_022761d0 *) self->buf_89c, (int) self);
            func_ov068_02275c78(self, 8);
            break;

        case 1:
            self->unk_560 = param;
            func_ov068_022761d0((UnkStruct_022761d0 *) self->buf_89c, (int) self);
            if (self->state == 0) {
                func_ov068_02275c78(self, 1);
            } else {
                func_ov068_02275c78(self, 8);
            }
            break;

        case 8:
            self->unk_A60 = 0x14;
            func_ov068_0227647c((UnkStruct_0227647c *) self);
            if (self->state == 0xA || self->state == 5) {
                break;
            }
            func_ov068_02275c78(self, 6);
            break;

        case 4:
            func_ov068_02275c78(self, 6);
            break;

        default:
            break;
    }
}

int func_ov068_0227629c(void *receiver)
{

    return func_0209bba0((char *) ((char *) (void *) func_02099640((int) func_020984e8()) + 0xb4)) != 0;
}

void func_ov068_02276278(void *receiver)
{
    if (func_ov068_0227629c(receiver) == 0) {

        func_0209bb90(func_02099640((int) func_020984e8()) + 0xb4, 1);
    }
}

int func_ov068_02276254(void *self)
{

    return (unsigned int) func_0209bba0((char *) ((unsigned int) func_02099640((int) func_020984e8()) + 0xb4)) > 1;
}

void func_ov068_02276230(void *receiver)
{
    if (func_ov068_02276254(receiver) != 0) {
        return;
    }

    func_0209bb90((char *) ((int) func_02099640((int) func_020984e8()) + 0xb4), 2);
}

int func_ov068_0227620c(void *self)
{
    if (func_0209bba0((char *) ((int) func_02099640(func_020984e8()) + 0xb4)) == 2) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov068_022761f0(void *receiver)
{

    func_0209bb90((char *) (func_02099640((int) func_020984e8()) + 0xb4), 3);
}

void func_ov068_022761d0(UnkStruct_022761d0 *obj, int val)
{
    func_0202dc3c(obj, val, 0x11);
    obj->unk_1A4 = val;
}
