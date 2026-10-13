/* func_02017ff4 @ 0x02017ff4, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern volatile unsigned short data_020c80f8;

extern int func_020164cc(void *p);
extern void func_02016764(void *p0, void *p1, int p2, unsigned short p3, int p4, int p5, int p6, int p7);
extern void func_02012444(u32 w, u16 v, int flag);
extern void func_02057cb8(void *p);
extern void func_0209129c(u32 w);
extern void func_02019af0(void *p, int v);
extern void func_02091278(u32 w, void *p1, void *p2, int p3);

void func_02017ff4(char *a, char *b)
{
    u16 v;
    u32 x;
    u32 w;

    if (func_020164cc(b + 0x334) != 0) {
        v = data_020c80f8;
        func_02016764(b + 0x334, b, 0, data_020c80f8, 0, 0x1000, 0, 0);
        x = *(u32 *) (b + 0x628);
        if (x != 0) {
            func_02012444(x, v, 0);
        }
        func_02057cb8(b);
        w = *(u32 *) (a + 0xac);
        if (w != -1) {
            func_0209129c(w);
        }
        func_02019af0(a, 1);
        *(u8 *) (a + 0x98) = 0x14;
    } else {
        w = *(u32 *) (a + 0xac);
        if (w != -1) {
            func_02091278(w, b + 0x478, b + 0x8e, 0);
        }
    }
}