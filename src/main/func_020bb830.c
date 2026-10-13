/* func_020bb830 @ 0x020bb830, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0209e474(void *p);
extern int func_0209dbe4(void *p);

int func_020bb830(int a, int b)
{
    u64 t;
    int r;

    r = 0;
    t = 0;
    func_0209e474(&t);
    if (b != 3) {
        if (b != 4) {
            goto done;
        }
    }
    switch (func_0209dbe4(&t)) {
        case 0:
        case 1:
        case 2:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
            r = 2;
            break;
        default:
            r = 1;
            break;
    }
done:
    return r;
}
