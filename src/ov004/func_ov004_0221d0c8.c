/* func_ov004_0221d0c8 @ 0x0221d0c8, 0xc0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern int func_ov004_0221c844(void *s, int a);
extern int func_0201c2a4(void *s, int a);
extern void func_02016108(void *p, int a);
extern int func_0203af80(Vec3 *v);
extern int func_0203b144(void);
extern void func_ov004_0221d1d8(void *s);

void func_ov004_0221d0c8(char *s, unsigned int sel, int a2)
{
    Vec3 v;
    v.x = *(int *) (s + 0x5c);
    v.y = *(int *) (s + 0x60);
    v.z = *(int *) (s + 0x64);
    v.y = v.y + 0x2000;
    switch (sel) {
        case 3:
            *(u8 *) (s + 0x560) = (u8) a2;
            func_ov004_0221c844(s, 4);
            break;
        case 0:
            *(u8 *) (s + 0x560) = (u8) a2;
            func_02016108(s + 0x8a0, func_0201c2a4(s, 4));
            func_0203af80(&v);
            func_ov004_0221c844(s, 5);
            break;
        case 1:
            *(u8 *) (s + 0x560) = (u8) a2;
            func_02016108(s + 0x8a0, func_0201c2a4(s, 4));
            func_0203af80(&v);
            func_ov004_0221c844(s, 8);
            break;
        case 8:
            func_0203b144();
            func_ov004_0221d1d8(s);
            func_ov004_0221c844(s, 0);
            break;
        case 4:
            func_ov004_0221c844(s, 0);
            break;
    }
}
