/* room_object_shop_design: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02213b54 @ 0x02213b54, 0x1c bytes, Thumb
 * func_ov004_02213b24 @ 0x02213b24, 0x30 bytes, Thumb
 * func_ov004_02213af0 @ 0x02213af0, 0x34 bytes, Thumb
 * func_ov004_02213ab8 @ 0x02213ab8, 0x38 bytes, Thumb
 * func_ov004_02213a08 @ 0x02213a08, 0xb0 bytes, Thumb
 * func_ov004_022139a8 @ 0x022139a8, 0x60 bytes, Thumb
 * func_ov004_02213984 @ 0x02213984, 0x24 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_022139a8 {
    int x, y, z;
};

extern int func_ov004_0221152c(unsigned int size);
extern void *const data_ov004_02251ec4[];
extern void *const data_ov004_02251f70[];
extern void *func_ov004_022110e4(void *p);
extern void func_020f5958(void *p);
extern void func_020f5948(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);
extern void *func_ov004_0220fde0(void *self);
extern int func_0204bc50(void *p, int a);
extern void *func_02072614(void);
extern void *func_02072628(void *a, u8 b);
extern int func_02057084(int a, void *d, void *p, int c, int e);
extern void func_0200451c(void *p);
extern int data_ov004_022531c8;
extern int func_0207277c(int a, int b);
extern int func_020044c0(void *p, int a, int b, int c);
extern void func_020044d0(void *p, struct UnkStruct_022139a8 *t);
extern int func_020044a0(char *p);

void *func_ov004_02213b24(char *self);

void func_ov004_02213b54(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x88c)))) {
        func_ov004_02213b24((char *) conditionInput0);
    }
}

void *func_ov004_02213b24(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02251ec4;
    *(const void **) (self + 0xec) = data_ov004_02251f70;
    func_020f5958(self + 0x848);
    return self;
}

void *func_ov004_02213af0(char *self)
{
    *(const void **) (self) = data_ov004_02251ec4;
    *(const void **) (self + 0xec) = data_ov004_02251f70;
    func_020f5948(self + 0x848);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_02213ab8(char *self)
{
    *(const void **) (self) = data_ov004_02251ec4;
    *(const void **) (self + 0xec) = data_ov004_02251f70;
    func_020f5948(self + 0x848);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_02213a08(char *self)
{
    int m;
    u16 t;
    volatile u16 v;
    void *r;
    int idx;

    v = (u16) func_0204bc50(func_ov004_0220fde0(self), 0);
    *(int *) (self + 0x844) = 0;
    m = 0;
    t = v;
    if (t >= 0x3e04 && t <= 0x3e23) {
        m = 1;
    }
    if (m != 0) {
        if (t >= 0x3e04 && t <= 0x3e23) {
            idx = (t - 0x3e04) >> 2;
        } else {
            idx = -1;
        }
        *(int *) (self + 0x844) = idx & 7;
        r = func_02072628(func_02072614(), (u8) * (int *) (self + 0x844));
        if (r != 0) {
            func_02057084(*(int *) (self + 0x594), &data_ov004_022531c8, r, 0, 0);
            if (*(u8 *) (self + 0x888) == 0) {
                func_0200451c(self + 0x848);
                *(u8 *) (self + 0x888) = 1;
            }
            return 1;
        }
    }
    return 0;
}

int func_ov004_022139a8(char *self)
{
    struct UnkStruct_022139a8 t;

    if (*(u8 *) (self + 0x888) != 0) {
        t = *(struct UnkStruct_022139a8 *) (self + 0x7b8);
        if (func_0207277c((int) func_02072614(), *(int *) (self + 0x844))) {
            func_020044c0(self + 0x848, 0x50, 0x7f, 0);
        }
        func_020044d0(self + 0x848, &t);
    }
    return 1;
}

int func_ov004_02213984(char *self)
{
    if (*(u8 *) (self + 0x888) != 0) {
        func_020044a0(self + 0x848);
    }
    return 1;
}
