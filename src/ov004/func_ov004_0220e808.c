/* func_ov004_0220e808 @ 0x0220e808, 0xe8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

union UA {
    struct {
        u16 a : 9;
        u16 b : 7;
    } unk_00;
    u16 w;
};
union UB {
    struct {
        u16 c : 4;
        u16 d : 4;
        u16 e : 1;
        u16 g : 6;
    } unk_00;
    u16 w;
};

extern int func_020b67ac(void);
extern int func_ov004_0220e5c8(void *self);
extern int *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(int *a, int v);
extern u16 func_020b65c4(void);
extern int func_ov004_0220e758(void *self, int *x, int *y, int p1, int p2);

u16 func_ov004_0220e808(char *self, int p1, int p2)
{
    union UA A;
    union UB B;
    int x;
    int y;

    if (func_020b67ac() != 0 || func_ov004_0220e5c8(self) != 0) {
        A.unk_00.a = func_ov004_0223cd78(func_ov004_0223ce84(), (int) self);
        A.unk_00.b = func_020b65c4();
        return A.w;
    }
    if (func_ov004_0220e758(self, &x, &y, p1, p2) != 0) {
        B.unk_00.c = x & 0xf;
        B.unk_00.d = y & 0xf;
        B.unk_00.e = *(u8 *) (self + 0x288) & 1;
        B.unk_00.g = func_020b65c4();
        return B.w;
    }
    return 0;
}
