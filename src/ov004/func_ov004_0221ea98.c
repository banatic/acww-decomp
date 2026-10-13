/* func_ov004_0221ea98 @ 0x0221ea98, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off
typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b;
} UnkStruct_0221ea98;
extern void func_0204f818(int *a, volatile int *b, void *p);
extern int func_02084e00(void *p, int x, int z);
extern int func_02084e20(void *p, int x, int z);
extern void func_0204f794(Vec3 *t, int x, int z);
extern UnkStruct_0221ea98 data_ov004_02257c98[];

int func_ov004_0221ea98(void *unused, int *out1, int *out2, char *self)
{
    int a;
    volatile int b;
    Vec3 t;
    u8 k;
    int x;
    int z;
    int ta;
    int tb;
    t.x = 0;
    t.y = 0;
    t.z = 0;
    a = 0;
    b = 0;
    k = (u8) ((*(short *) (self + 0x8e) >> 14) & 3);
    func_0204f818(&a, &b, self + 0x5c);
    ta = a;
    tb = b;
    x = ta + data_ov004_02257c98[k].a;
    z = tb + data_ov004_02257c98[k].b;
    if ((unsigned int) b < 0xe) {
        if (func_02084e00(self + 0x8b4, x, z) != 0) {
            func_0204f794(&t, x, z);
            *out1 = t.x;
            *out2 = t.z;
            return 1;
        }
    } else {
        if (func_02084e20(self + 0x8b4, x, z) != 0) {
            func_0204f794(&t, x, z);
            *out1 = t.x;
            *out2 = t.z;
            return 1;
        }
    }
    return 0;
}
