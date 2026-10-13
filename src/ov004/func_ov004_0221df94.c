/* func_ov004_0221df94 @ 0x0221df94, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern void func_0203af80(Vec3 *v);
extern void func_0203b144(int a);
extern int func_ov004_0221e048(void *self);
extern int func_ov004_0221dd24(void *self, int a);

void func_ov004_0221df94(char *self, unsigned int sel, int a2)
{
    Vec3 v;
    v.x = *(int *) (self + 0x5c);
    v.y = *(int *) (self + 0x60);
    v.z = *(int *) (self + 0x64);
    v.y = v.y + 0x2000;
    switch (sel) {
        case 3:
            *(u8 *) (self + 0x560) = (u8) a2;
            func_ov004_0221dd24(self, 4);
            break;
        case 0:
            *(u8 *) (self + 0x560) = (u8) a2;
            func_0203af80(&v);
            func_ov004_0221dd24(self, 5);
            break;
        case 8:
            func_0203b144(func_ov004_0221e048(self));
            func_ov004_0221dd24(self, 0);
            break;
        case 4:
            func_ov004_0221dd24(self, 0);
            break;
    }
}
