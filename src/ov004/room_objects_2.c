/* room_objects_2: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223bbc0 @ 0x0223bbc0, 0x3a bytes, Thumb
 * func_ov004_0223bb88 @ 0x0223bb88, 0x38 bytes, Thumb
 * func_ov004_0223bb20 @ 0x0223bb20, 0x68 bytes, Thumb
 * func_ov004_0223bb14 @ 0x0223bb14, 0xc bytes, Thumb
 * func_ov004_0223badc @ 0x0223badc, 0x38 bytes, Thumb
 * func_ov004_0223bac8 @ 0x0223bac8, 0x14 bytes, Thumb
 */

#include "types.h"

extern int func_020961a8(int argument0);
extern int func_ov004_0223bbfc(int *argument0, int *argument1, void *argument2, int argument3, void *argument4,
                               void *argument5);
extern unsigned int func_ov004_0223c130(void);
extern void *func_ov004_0223ce84(void);
extern char *func_ov004_0223cd58(void *, unsigned int);
extern int func_ov004_0220ccf8(void *self, int idx);
extern void func_ov004_0220e578(u16 *dst, void *p);
extern int func_ov004_0220fde0(void *self);
extern u16 func_0204bc50(int x, int y);
extern char data_ov004_0225967c[];

int func_ov004_0223bbc0(char *self, int a1, int a2, int a3)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020961a8((int) ((int) (0x4)));
    if (v1 != 0x0) {
        return func_ov004_0223bbfc((int *) (self), (int *) (a1), (void *) ((char *) v1 + 0x5c),
                                   (int) (*(short *) ((char *) v1 + 0x8e)), (void *) (a2), (void *) (a3));
    }
    return -0x1;
}

int func_ov004_0223bb88(unsigned int i)
{
    if (i < func_ov004_0223c130()) {
        if (func_ov004_0223cd58(func_ov004_0223ce84(), i) != 0) {
            return *(u8 *) (func_ov004_0223cd58(func_ov004_0223ce84(), i) + 0x288);
        }
    }
    return 0;
}

int func_ov004_0223bb20(unsigned int idx, u16 *pb, u16 *pc)
{
    u16 tmp;
    void *o;
    if (pb != 0) {
        *pb = 0xfff1;
    }
    if (pc != 0) {
        *pc = 0xfff1;
    }
    o = (void *) func_ov004_0223cd58(func_ov004_0223ce84(), idx);
    if (o != 0) {
        func_ov004_0220ccf8(o, 5);
        if (pb != 0) {
            func_ov004_0220e578(&tmp, o);
            *pb = tmp;
        }
        if (pc != 0) {
            *pc = func_0204bc50(func_ov004_0220fde0(o), 0);
        }
        return 1;
    }
    return 0;
}

int func_ov004_0223bb14(int a)
{
    return func_ov004_0223bb20(a, 0, 0);
}

char *func_ov004_0223badc(int a)
{
    char *p = func_ov004_0223cd58(func_ov004_0223ce84(), a);
    if (p == 0) {
        return data_ov004_0225967c;
    }
    if (*(int *) (p + 0x150) < 0x4cd) {
        return data_ov004_0225967c;
    }
    return 0;
}

void func_ov004_0223bac8(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) ((char *) ((void **) data_ov004_0225967c)) = *(int *) (self);
    *(int *) ((char *) ((void **) data_ov004_0225967c) + 0x4) = *(int *) (self + 0x4);
    *(int *) ((char *) ((void **) data_ov004_0225967c) + 0x8) = *(int *) (self + 0x8);
}
