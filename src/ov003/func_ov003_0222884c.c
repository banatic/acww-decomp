/* func_ov003_0222884c @ 0x0222884c, 0x94 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern void *data_021c67a4;
extern Vec3 data_021c67d0;
extern int func_ov003_0222799c(void *p, Vec3 *v, int a, int b, int c);
extern void func_ov003_02228cd4(void *a0);
extern void func_ov003_02228d48(void *a0, void *c);

void func_ov003_0222884c(void *a0, char *b, void *c)
{
    Vec3 v;
    if (data_021c67a4 != 0) {
        v.x = data_021c67d0.x;
        v.y = data_021c67d0.y;
        v.z = data_021c67d0.z;
        if (func_ov003_0222799c(b + 0x120, &v, 0xa000, 0x10000, 0xa000)) {
            *(int *) (b + 0x80) = 3;
            *(int *) (b + 0x244) = -1;
        } else {
            int *p = (int *) (b + 0x244);
            int t = *p;
            if (t != -1) {
                if (t == 0) {
                    if (*(u8 *) (b + 0x7f)) {
                        func_ov003_02228cd4(a0);
                    }
                    func_ov003_02228d48(a0, c);
                } else {
                    *p = t - 1;
                }
            }
        }
    }
}
