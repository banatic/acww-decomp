/* func_0205d528 @ 0x0205d528, 0x64 bytes, Thumb, module main
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

int func_0205d528(void *self, u16 *key)
{
    void *ptr;
    int i;
    int r;

    for (i = 0; i < 10; i++) {
        ptr = (char *) self + 0x28 + (i << 1);
        if (func_0204bcdc(ptr)) {
            r = EqA(ptr, key);
        } else {
            r = EqB(*(u16 *) ((char *) self + (i << 1) + 0x28), *key);
        }
        if (r != 0) {
            return i;
        }
    }
    return 10;
}
