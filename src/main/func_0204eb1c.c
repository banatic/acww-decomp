/* func_0204eb1c @ 0x0204eb1c, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 *func_0204f5e0(void *b, int cx, int cy, int ox, int oy, int layer);
extern int func_020b3b14(void);
extern int func_ov003_02220460(int h, int a1, int a2, int a3, int f);
extern int func_0204ef24(void *b, int a1, int a2, int a3);
extern int func_0204bd08(u16 *p);
extern int func_0204bcdc(u16 *p);
extern void func_0203a76c(u16 v);

int func_0204eb1c(void *b, int a1, int xx, int yy, u8 flag)
{
    u16 h;
    u16 *p;
    int cx;
    int cy;

    cx = xx >> 4;
    cy = yy >> 4;
    p = func_0204f5e0(b, cx, cy, xx - (cx << 4), yy - (cy << 4), 0);
    h = 0xfff1;
    if (p != 0) {
        h = *p;
    }
    if (flag != 0 && func_020b3b14() != 0) {
        return func_ov003_02220460(func_020b3b14(), a1, xx, yy, 1);
    }
    if (func_0204ef24(b, a1, xx, yy) != 0) {
        if (func_0204bd08(&h) != 0 || func_0204bcdc(&h) != 0) {
            func_0203a76c(h);
        }
        return 1;
    }
    return 0;
}
