/* room_etc_board_3: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221b01c @ 0x0221b01c, 0x4 bytes, Thumb
 * func_ov004_0221b00c @ 0x0221b00c, 0x10 bytes, Thumb
 * func_ov004_0221afe8 @ 0x0221afe8, 0x24 bytes, Thumb
 * func_ov004_0221afb8 @ 0x0221afb8, 0x30 bytes, Thumb
 * func_ov004_0221af84 @ 0x0221af84, 0x34 bytes, Thumb
 * func_ov004_0221af2c @ 0x0221af2c, 0x58 bytes, Thumb
 * func_ov004_0221af08 @ 0x0221af08, 0x22 bytes, Thumb
 */

#include "types.h"

extern u8 data_ov004_022577ac;
extern int data_ov004_02257804[];
extern int func_020ea990(void *a, void *b);
extern int func_020e8b4c(int a, int b);
extern int func_ov004_0221ae7c(int a, int b);

int func_ov004_0221af84(char *self);

int func_ov004_0221b01c(void)
{
    return 1;
}

int func_ov004_0221b00c(char *arg0)
{
    func_ov004_0221af84((char *) arg0);
    return 1;
}

void func_ov004_0221afe8(void)
{
    unsigned int i;
    int z = 0;
    if (data_ov004_022577ac != 0) {
        return;
    }
    for (i = 0; i < 0x40; i++) {
        data_ov004_02257804[i] = z;
    }
}

int func_ov004_0221afb8(void *self)
{
    u8 *p = (u8 *) ((char *) self + 0x154);
    *p = data_ov004_022577ac;
    if (*p < 0x40) {
        ((void * *) data_ov004_02257804)[*p] = self;
        data_ov004_022577ac = data_ov004_022577ac + 1;
        return 1;
    }
    return 0;
}

int func_ov004_0221af84(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x154) < 0x40) {
        *(void **) ((char *) ((void * *) data_ov004_02257804) + (*(u8 *) (self + 0x154) << 2)) = 0x0;
        *(u8 *) ((char *) ((void * *) &data_ov004_022577ac)) = (*(u8 *) ((char *) ((void * *) &data_ov004_022577ac)) - 0x1);
        *(u8 *) (self + 0x154) = 0xff;
        return 0x1;
    }
    return 0x0;
}

int func_ov004_0221af2c(char *self, char *other)
{
    int lim = *(int *) (self + 0x158) + 0x2ccd;

    if (other != 0 && func_020ea990(other + 0x5c, self + 0x5c) < lim &&
        func_020e8b4c((s16) (*(s16 *) (self + 0x8e) + 0x8000), *(s16 *) (other + 0x8e)) < 0x1300) {
        return 1;
    }
    return 0;
}

void func_ov004_0221af08(int a, int b)
{
    switch (b) {
        case 0:
            func_ov004_0221ae7c(a, 1);
            break;
        case 8:
            func_ov004_0221ae7c(a, 0);
            break;
        default:
            break;
    }
}
