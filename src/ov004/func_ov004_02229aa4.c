/* func_ov004_02229aa4 @ 0x02229aa4, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern int func_02056f94(void *);
extern int func_02073908(void *, int);
extern int func_02008258(void *, int);
extern void func_ov004_0223cb10(void);
extern int func_ov004_0223c85c(void);
extern int func_020b67d4(void);
extern void func_0200f328(void *, int);
extern int func_0200dc10(void *);
extern int func_0200dc8c(void *);
extern void func_ov004_0222a23c(void *, int, int, int, int);
extern void func_ov004_02229928(void *, int, int);
extern void func_ov004_0223c820(void);

void func_ov004_02229aa4(char *self)
{
    u8 m;
    int k;
    if (func_02056f94(self + 0x2d0) != 0) {
        if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
            m = 0;
            func_ov004_0223cb10();
            if (func_ov004_0223c85c() == 0) {
                m = 1;
            }
            if (func_020b67d4() == 0 || *(int *) (self + 0x800) != 0) {
                m = (u8) (m | 2);
            }
            if (m != 0) {
                char *q = self + 0x7d4;
                if (*(u8 *) q == 0) {
                    *(u8 *) q = 1;
                    if (m == 1) {
                        func_0200f328(self, 0x6d);
                    }
                }
                k = func_0200dc10(self);
                if (func_0200dc8c(self) > 0 && k == 2) {
                    return;
                }
                *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
                func_ov004_0222a23c(self, 0, 1, 5, -1);
            } else {
                func_ov004_02229928(self, 6, -1);
                func_ov004_0223cb10();
                func_ov004_0223c820();
            }
        } else {
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        }
    }
}
