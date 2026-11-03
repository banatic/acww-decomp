/* room_object_02253058_11: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221882c @ 0x0221882c, 0x1c bytes, Thumb
 * func_ov004_022187ec @ 0x022187ec, 0x40 bytes, Thumb
 * func_ov004_022187b8 @ 0x022187b8, 0x34 bytes, Thumb
 * func_ov004_02218780 @ 0x02218780, 0x38 bytes, Thumb
 * func_ov004_0221876c @ 0x0221876c, 0x14 bytes, Thumb
 * func_ov004_02218734 @ 0x02218734, 0x38 bytes, Thumb
 */

#include "types.h"

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_0220d110(void *);
extern void *func_ov004_022110e4(void *);
extern void *const data_ov004_02253058[];
extern void *const data_ov004_02253104[];
extern void *func_ov004_0220d0f4(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);
extern int func_02073d90(int);
extern void *data_020ccf94;

void *func_ov004_022187ec(char *self);

void func_ov004_0221882c(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x8b8)))) {
        func_ov004_022187ec((char *) conditionInput0);
    }
}

void *func_ov004_022187ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022110e4(self);
    *(void **) (self) = ((void * *) data_ov004_02253058);
    *(void **) (self + 0xec) = ((void * *) data_ov004_02253104);
    *(u16 *) (self + 0x85c) = 0xfff1;
    func_ov004_0220d110(self + 0x860);
    return self;
}

void *func_ov004_022187b8(char *self)
{
    *(const void **) (self) = data_ov004_02253058;
    *(const void **) (self + 0xec) = data_ov004_02253104;
    func_ov004_0220d0f4(self + 0x860);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_02218780(char *self)
{
    *(const void **) (self) = data_ov004_02253058;
    *(const void **) (self + 0xec) = data_ov004_02253104;
    func_ov004_0220d0f4(self + 0x860);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_0221876c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x85e) >= 0x1) {
        return 0x1;
    }
    return 0x0;
}

int func_ov004_02218734(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02073d90(*(int *) ((char *) &data_020ccf94)) == 0x0 && func_ov004_0221876c((char *) self) != 0x0 &&
        *(int *) (self + 0x858) != 0x0) {
        return 0x1;
    } else {
        return 0x0;
    }
}
