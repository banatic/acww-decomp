/* func_02037da8 @ 0x02037da8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02037e0c(int, int, int, u8);
extern void func_02037d14(int *, int *, int);

int func_02037da8(int p0, int *p1, int *p2, u16 *p3, u16 *p4, u8 b5)
{
    u16 *p;
    int found;

    p = (u16 *) func_02037e0c(p0, 0, 0, b5);
    found = 0;
    if (p != 0) {
        int i = found;
        while (i < 0x100) {
            u16 hi = *p4;
            unsigned int ok = found;
            u16 cur = *p;
            u16 lo = *p3;
            if (cur >= lo && cur <= hi) {
                ok = 1;
            }
            if (ok != 0) {
                func_02037d14(p1, p2, i);
                found = 1;
                break;
            }
            p++;
            i++;
        }
    }
    return found;
}
