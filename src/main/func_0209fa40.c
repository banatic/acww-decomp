/* func_0209fa40 @ 0x0209fa40, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0209fa30(u8 *p);
extern void func_0209e474(void *p);
extern void func_0209e29c(void *p, int n);
extern int func_0209e3ac(const void *a, const void *b, int mask);

void func_0209fa40(u8 *arg)
{
    u64 t[2];

    if (func_0209fa30(arg) == 0) {
        return;
    }
    t[0] = 0;
    t[1] = 0;
    func_0209e474(&t[0]);
    ((u8 *) t)[13] = arg[2];
    ((u8 *) t)[12] = arg[1];
    ((u8 *) t)[11] = arg[0];
    ((u8 *) t)[10] = 0;
    if (func_0209e3ac(&t[1], &t[0], 0x3c) == 1) {
        goto zero;
    }
    ((u8 *) t)[10] = 6;
    func_0209e29c(&t[1], 1);
    if (func_0209e3ac(&t[1], &t[0], 0x3c) == 1) {
        return;
    }
    arg[3] = 0;
    return;
zero:
    arg[3] = 0;
}
