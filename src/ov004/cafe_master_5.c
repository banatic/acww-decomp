/* cafe_master_5: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02224978 @ 0x02224978, 0x3c bytes, Thumb
 * func_ov004_022248b0 @ 0x022248b0, 0xc8 bytes, Thumb
 * func_ov004_02224844 @ 0x02224844, 0x6c bytes, Thumb
 * func_ov004_022247b4 @ 0x022247b4, 0x90 bytes, Thumb
 * func_ov004_022247b0 @ 0x022247b0, 0x4 bytes, Thumb
 * func_ov004_022247ac @ 0x022247ac, 0x4 bytes, Thumb
 * func_ov004_02224770 @ 0x02224770, 0x3c bytes, Thumb
 * func_ov004_02224740 @ 0x02224740, 0x30 bytes, Thumb
 * func_ov004_0222473c @ 0x0222473c, 0x4 bytes, Thumb
 * func_ov004_0222471c @ 0x0222471c, 0x20 bytes, Thumb
 * func_ov004_022246e4 @ 0x022246e4, 0x38 bytes, Thumb
 */

#include "types.h"

extern int func_02019d0c(void *s, int kind, int value, int r3val, int argA, short argB, short argC, int argD, int argE,
                         unsigned short argF, unsigned short argG);
extern unsigned short data_020c80f8;
extern int func_02073d90(void *p);
extern short *func_0209d358(int a, int b);
extern int func_020960f8(int a, int b);
extern int func_0203e070(char *self, int a);
extern void func_ov004_022249b4(char *self, int a);
extern void *data_020ccf94;
extern unsigned char data_021fbee8[];
extern int func_02016104(void *p);
extern void func_0201ad18(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_0201c314(void *self, int n);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *p);
extern int func_ov004_0222c070(int k);
extern void func_0208b514(unsigned int value);
extern int func_0203e020(void *self);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern unsigned char data_020c814c[];

int func_ov004_02224978(char *self)
{
    *(int *) (self + 0x778) = 0;
    func_02019d0c((void *) (self + 0x564), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov004_022248b0(char *self)
{
    // DECLS
    // ENDDECLS

    if (*(int *) (self + 0x778) > 0) {
        *(int *) (self + 0x778) = *(int *) (self + 0x778) + 1;
        if (*(int *) (self + 0x778) > 0x14) {
            func_0201ad18((void *) (self + 0x3b0), 0, 0, 0, (unsigned int) data_021fbee8, 4, (*(int *) data_020c814c), 1);
            *(int *) (self + 0x778) = -1;
        }
    } else if (*(int *) (self + 0x778) == 0) {
        if (*(short *) (self + 0x3d2) > 0x2000) {
            *(int *) (self + 0x778) = 1;
        }
    }
    if (func_02073d90(data_020ccf94) == 0) {
        if (*func_0209d358(0, 0x4a) == 0) {
            if (func_020960f8(0x27, 4) != 0) {
                func_0203e070(self, 0);
            }
        }
    }
    if (*(short *) (self + 0x714) != *(short *) (self + 0x8e)) {
        func_ov004_022249b4(self, 3);
        return 1;
    }
    return 1;
}

int func_ov004_02224844(char *self)
{
    int n;
    int r;

    n = func_02016104(self + 0x658);
    r = 0;
    func_0201ad18(self + 0x3b0, 1, 0, 0, (int) ((int *) data_021fbee8), 4, (*(int *) data_020c814c), 1);
    if (n != 0) {
        r = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, r, 0);
    return 1;
}

int func_ov004_022247b4(char *self)
{
    if (func_02014868(self + 0x618) == 0) {
        if (func_02073d90((*(char **) &data_020ccf94)) == 0) {
            if (*func_0209d358(0, 0x4a) == 0) {
                int value = func_020960f8(0x28, 4);
                if (value != 0) {
                    value = func_ov004_0222c070(2);
                }
                func_0208b514(value);
            }
        }
        func_0201ad18(self + 0x3b0, 0, 0, 0, (int) ((int *) data_021fbee8), 4, (*(int *) data_020c814c), 1);
        func_0203e020(self);
        func_ov004_022249b4((char *) self, 2);
    }
    return 1;
}

int func_ov004_022247b0(void)
{
    return 1;
}

int func_ov004_022247ac(void)
{
    return 1;
}

int func_ov004_02224770(char *self)
{
    // DECLS
    // ENDDECLS
    func_02019d0c(self + 0x564, 0x3, 0x2, 0x0, 0x0, 0x0, *(short *) (self + 0x714), 0x0, 0x0,
                  *(u16 *) ((char *) ((void **) &data_020c80f8)), 0x0);
    return 0x1;
}

int func_ov004_02224740(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov004_022249b4((char *) self, 0);
        }
    }
    return 1;
}

int func_ov004_0222473c(void)
{
    return 1;
}

int func_ov004_0222471c(char *self)
{
    if (func_020960f8(0x28, 4) != 0) {
        func_ov004_022249b4(self, 1);
    }
    return 1;
}

int func_ov004_022246e4(int a)
{
    func_0201ad18((void *) (a + 0x3b0), 0, 0, 0, (unsigned int) data_021fbee8, 4, *((int *) data_020c814c), 1);
    return 1;
}
