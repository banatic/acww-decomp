/* func_020a1bdc @ 0x020a1bdc, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 **data_021f3c3c;
extern u8 data_021dc7a8[];

extern int func_020a1b68(void *a0, void *a1);
extern int func_02050920(u8 *p, int n);
extern int func_0209f180(u8 *p);
extern int func_02098844(u8 *p, int i);
extern u8 *func_02099664(int);
extern u8 *func_02099658(int);

int func_020a1bdc(void *a0, void *a1)
{
    volatile char pad[4];
    u8 *b;
    u8 *p;
    int r;
    int t;
    int i;

    if (a1 != 0 && data_021f3c3c == 0) {
        return 1;
    }
    r = func_020a1b68(a0, a1);
    if (r != 0) {
        goto done;
    }
    if (a1 != 0) {
        b = *(u8 **) ((char *) data_021f3c3c + 0xb0);
    } else {
        b = data_021dc7a8;
    }
    t = func_02050920(b, 0x173fc);
    if (func_0209f180(b) == 0) {
        return 4;
    }
    if (t == 0) {
        func_02050920(b + 0x11c70, 0x950);
        i = 0;
        p = b + 0x14;
        do {
            func_02050920(func_02099664((int) func_02098844(p, i)), 0x50);
            func_02050920(func_02099658((int) func_02098844(b + 0x14, i)), 0x484);
            i++;
        } while (i < 4);
    } else {
        return 4;
    }
done:
    return r;
}
