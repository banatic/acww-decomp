/* func_ov004_022414a8 @ 0x022414a8, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02244764(void *self);
extern void func_02056fcc(void *, int, int, int, int);
extern void func_ov004_02244be0(void *self, int a);

void func_ov004_022414a8(char *self)
{
    char *p;
    int q;
    func_ov004_02244764(self);
    if (*(signed char *) (self + 0x196) == 0x14) {
        p = self + 0xb0;
        if (*(short *) (self + 0x9c) >= *(short *) (self + 0x9e) || *(u8 *) (self + 0x50) != 0) {
            if (((unsigned int) (*(int *) (p + 0xa4) << 4) >> 16) == 0) {
                func_02056fcc(p + 0x9c, 4, 1, 0x1000, 0);
                *(u8 *) (self + 0x50) = 0x3c;
            } else if (*(u8 *) (self + 0x50) != 0) {
                *(u8 *) (self + 0x50) = (u8) (*(u8 *) (self + 0x50) - 1);
            }
        } else {
            q = *(int *) (p + 0xa4) >> 12;
            if ((u16) q != 0 || ((unsigned int) (*(int *) (p + 0xa0) << 4) >> 16) != 0) {
                func_02056fcc(p + 0x9c, 0, 3, 0x1000, (u16) q);
            }
        }
    }
    if (*(u8 *) (self + 0x22) != 0) {
        if (*(short *) (self + 0x9c) < *(short *) (self + 0x9e)) {
            if (*(u8 *) (self + 0x50) == 0) {
                func_ov004_02244be0(self, 0);
            } else {
                *(u8 *) (self + 0x50) = (u8) (*(u8 *) (self + 0x50) - 1);
            }
        } else {
            *(u8 *) (self + 0x50) = 0x3c;
        }
    }
}
