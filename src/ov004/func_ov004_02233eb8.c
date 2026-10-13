/* func_ov004_02233eb8 @ 0x02233eb8, 0x46 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int m[12];
} Mtx;
extern void func_02055e90(void *, int);
extern u16 func_02065604(void);
extern void NNS_G3dMdlSetMdlEmi(void *, int, u16);

void func_ov004_02233eb8(void *a, char *b, Mtx m)
{
    volatile u16 t, u;
    if (b != 0) {
        *(Mtx *) (b + 0x64) = m;
        func_02055e90(b, 0);
        t = func_02065604();
        u = t;
        NNS_G3dMdlSetMdlEmi(*(void **) (b + 0x5c), 0, u);
    }
}
