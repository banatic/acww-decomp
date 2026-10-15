/* func_ov004_02229d7c @ 0x02229d7c, 0xf4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0200dc8c(void *);
extern void func_ov004_02229ea8(void *, int);
extern int func_02008258(void *, int);
extern int func_0200dc10(void *);
extern int func_ov004_0222a23c(void *, int, int, int, int);
extern int func_02056f94(void *);
extern int func_0200d4e8(void *, int, int, int);
extern void func_02056fcc(void *, int, int, int, unsigned);

void func_ov004_02229d7c(char *self)
{
    if (*(u8 *) (self + 0x2e4) == 3) {
        char *q = self + 0x7d4;
        int k;
        if (*(u8 *) q == 0 && func_0200dc8c(self) < 0x19a) {
            func_ov004_02229ea8(q, 1);
        }
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        k = func_0200dc10(self);
        if (*(u8 *) q != 0 && func_0200dc8c(self) > 0x19a && (k == 3 || k == 1)) {
            func_ov004_0222a23c(self, 1, 1, 5, -1);
        } else if (func_02056f94(self + 0x2d0) != 0) {
            if (*(u8 *) (self + 0x141) != 0) {
                func_ov004_0222a23c(self, 0, 1, 5, -1);
            } else {
                func_0200d4e8(self, 3, 1, -1);
            }
        }
    } else if (func_02056f94(self + 0x2d0) != 0) {
        func_02056fcc(self + 0x2d0, 0, 3, 0x1000, ((unsigned) *(int *) (self + 0x2d4) << 4) >> 16);
    }
}
