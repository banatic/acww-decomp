/* func_ov003_0222807c @ 0x0222807c, 0xd4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern void *data_021c67a4;
extern Vec3 data_021c67d0;
extern int func_ov003_0222799c(char *p, Vec3 *v, int a, int b, int c);
extern void func_ov003_02228cd4(char *self);
extern void func_ov003_02228d48(char *self, int k);
extern int func_ov003_0222a330(char *obj);

void func_ov003_0222807c(char *self, char *obj, int k)
{
    Vec3 t;
    if (*(u8 *) (obj + 0x23c) == 0 || *(u8 *) (obj + 0x224) == 6) {
        if (data_021c67a4 != 0) {
            t.x = data_021c67d0.x;
            t.y = data_021c67d0.y;
            t.z = data_021c67d0.z;
            if (func_ov003_0222799c(obj + 0x120, &t, 0xa000, 0x10000, 0xa000) == 0) {
                if (*(u8 *) (obj + 0x200) == 5 || *(u8 *) (obj + 0x224) == 6) {
                    if (*(u8 *) (obj + 0x7f)) {
                        func_ov003_02228cd4(self);
                    }
                    func_ov003_02228d48(self, k);
                } else {
                    if ((unsigned) (*(u8 *) (obj + 0x1fe) - 4) <= 2) {
                        if (func_ov003_0222a330(obj)) {
                            *(int *) (obj + 0x244) = 0x12c;
                        } else {
                            *(int *) (obj + 0x244) = 0x4b0;
                        }
                    } else {
                        *(int *) (obj + 0x244) = 0x4b0;
                    }
                    *(int *) (obj + 0x80) = 4;
                }
            }
        }
    }
}
