/* func_ov004_02211ed4 @ 0x02211ed4, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0221041c(void *self, int a, int b, int c, int d);
extern void *func_ov004_0220fde0(void *self);
extern int func_ov004_0223a760(void *p);
extern u16 func_020644cc(int a);
extern u16 func_ov004_0221062c(void *self, int k);

int func_ov004_02211ed4(char *self)
{
    int v;

    func_ov004_0221041c(self, 0, 1, 0x1000, 0);
    v = func_ov004_0223a760(func_ov004_0220fde0(self));
    switch (v) {
        case 0x3f9:
            *(u8 *) (self + 0x848) = 4;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
        case 0x3fb:
            *(u8 *) (self + 0x848) = 4;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
        case 0x3fa:
            *(u8 *) (self + 0x848) = 4;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
        case 0x3fc:
            *(u8 *) (self + 0x848) = 2;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
        default:
            *(u8 *) (self + 0x848) = 1;
            *(u16 *) (self + 0x844) = *(u8 *) (self + 0x848);
            break;
    }
    *(u8 *) (self + 0x849) = 0;
    *(u16 *) (self + 0x846) = 0;
    if (*(int *) (self + 0x76c) != 1) {
        if (v == 0x3fc) {
            *(u16 *) (self + 0x846) = func_020644cc(0x3c);
        } else if ((u16) (v + 0xfc07) <= 2) {
            *(u16 *) (self + 0x846) = func_020644cc(0xc8);
        } else {
            *(u16 *) (self + 0x846) = func_020644cc(func_ov004_0221062c(self, 0) * *(u16 *) (self + 0x844));
        }
    }
    return 1;
}
