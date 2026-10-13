/* func_020aff84 @ 0x020aff84, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020b0038(int i, int p1, int p2, unsigned int p3, int a0);
extern int func_0204bcdc(void *ptr);
extern int func_0204bc64(void *ptr);
extern u16 data_021f49f4;

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

int func_020aff84(void *p0, int p1, int p2, unsigned int p3)
{
    unsigned int i;
    void *ptr;
    int cond;
    int cond2;

    for (i = 0; i < p3; i++) {
        ptr = (void *) func_020b0038(i, p1, p2, p3, 0);

        if (func_0204bcdc(ptr)) {
            cond = EqA(ptr, p0);
        } else {
            cond = EqB(*(u16 *) ptr, *(u16 *) p0);
        }

        if (cond) {
            if (func_0204bcdc(p0)) {
                cond2 = EqA(p0, &data_021f49f4);
            } else {
                cond2 = EqB(*(u16 *) p0, data_021f49f4);
            }
            if (cond2 == 0) {
                return i;
            }
        }
    }
    return -1;
}
