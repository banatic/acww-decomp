/* func_ov004_02220e40 @ 0x02220e40, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern Vec3 *func_02095794(int a);
extern int func_02014868(void *p);
extern int func_020b5e10(void);
extern void func_020b6098(int h, int a);
extern void func_020b5ee4(int h, int a);
extern void func_ov004_02221550(void *s, int a);

int func_ov004_02220e40(char *s)
{
    volatile Vec3 v;
    Vec3 *q = func_02095794(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    if (func_02014868(s + 0x618) == 0) {
        if (*(u8 *) (s + 0xac8) == 5) {
            func_020b6098(func_020b5e10(), 0);
        } else {
            func_020b5ee4(func_020b5e10(), 0);
            func_020b6098(func_020b5e10(), 6);
        }
        func_ov004_02221550(s, 8);
    }
    return 1;
}
