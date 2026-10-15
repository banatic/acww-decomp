/* func_ov003_022289b4 @ 0x022289b4, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern void *data_021c67a4;
extern Vec3 data_021c67d0;

extern int func_ov003_0222799c(void *p, Vec3 *v, int a, int b, int c);
extern int func_ov003_02228dfc(void *a0, void *c);
extern int func_ov003_02228d1c(void *a0);

void func_ov003_022289b4(void *a0, char *b, void *c)
{
    Vec3 v;
    if (data_021c67a4 != 0) {
        v.x = data_021c67d0.x;
        v.y = data_021c67d0.y;
        v.z = data_021c67d0.z;
        if (func_ov003_0222799c(b + 0x12c, &v, 0xa000, 0x10000, 0xa000)) {
            func_ov003_02228dfc(a0, c);
            if (*(u8 *) (b + 0x7f)) {
                func_ov003_02228d1c(a0);
            }
        }
    }
}
