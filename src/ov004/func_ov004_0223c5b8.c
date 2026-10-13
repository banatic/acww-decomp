/* func_ov004_0223c5b8 @ 0x0223c5b8, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *base, int x, int y, int layer);
extern int func_02034270(void *buf, void *vec, int a, int b);
extern int func_020341c8(void *buf, int flag);
extern void func_0203423c(void *buf);

int func_ov004_0223c5b8(int x, int y)
{
    int v[3];
    char buf[0x40];
    char *o;
    int r;
    o = (char *) func_ov004_0223cc10(func_ov004_0223cd50(), x, y, 0);
    if (o != 0) {
        if (*(u8 *) (o + 0x78c) == 1) {
            return *(int *) (o + 0x60);
        }
        return *(int *) (o + 0x790) + *(int *) (o + 0x60);
    }
    v[0] = (x << 13) + 0x1000;
    v[1] = 0;
    v[2] = (y << 13) + 0x1000;
    func_02034270(buf, v, 0, 0);
    r = func_020341c8(buf, 0);
    func_0203423c(buf);
    return r;
}
