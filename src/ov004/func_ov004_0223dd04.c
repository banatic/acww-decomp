/* func_ov004_0223dd04 @ 0x0223dd04, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055d80(void *, int);
extern void NNSi_G3dModifyPolygonAttrMask(int, int, int);
extern void func_02055d38(void *, u8);
extern void func_0205510c(void *, int);
extern void func_020acc0c(void *, int, int, int);

int func_ov004_0223dd04(char *self)
{
    char *p;
    if (*(int *) (self + 0x110) != 4) {
        p = self + 0x5c;
        if (*(unsigned int *) (self + 8) > 0x1f) {
            *(int *) (self + 8) = 0x1f;
        }
        func_02055d80(self + 0x120, 3);
        NNSi_G3dModifyPolygonAttrMask(*(int *) (self + 0x17c), 1, 0x1f0000);
        func_02055d38(self + 0x120, (u8) * (int *) (self + 8));
        func_0205510c(self + 0x120, 0);
        if (*(unsigned int *) (self + 8) >= 0x1f && *(int *) (self + 0x110) == 1) {
            func_020acc0c(p, 0x400, 0x4000, 0x1000);
        }
    }
    return 1;
}
