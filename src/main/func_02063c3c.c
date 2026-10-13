/* func_02063c3c @ 0x02063c3c, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);

static __inline int EqA(void *a, void *b)
{
    if (func_0204bc64(a) == func_0204bc64(b)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 a, u16 b)
{
    if (a == b) {
        return 1;
    }
    return 0;
}

int func_02063c3c(u16 *target, u16 *arr, unsigned int count)
{
    unsigned int i;
    int r;

    for (i = 0; i < count; i++) {
        if (func_0204bcdc(arr)) {
            r = EqA(arr, target);
        } else {
            r = EqB(*arr, *target);
        }
        if (r != 0) {
            return i;
        }
        arr++;
    }
    return -1;
}
