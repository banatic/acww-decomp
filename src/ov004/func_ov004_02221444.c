/* func_ov004_02221444 @ 0x02221444, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern int func_020e8858(void *p);
extern int func_020644cc(int);
extern char *func_020961a8(int a);
extern int func_020ea990(Vec3 *v, void *p);
extern int func_020044c0(void *p, int a, int b, int c);
extern int func_0203e0a8(void *s, int a);

int func_ov004_02221444(char *s)
{
    Vec3 v;
    char *o;
    Vec3 *p;
    if (*(u8 *) (s + 0xadd) == 0) {
        if (func_020e8858(s + 0xadf) != 0) {
            return 1;
        }
        if (func_020644cc(0x65) > 0x19) {
            *(u8 *) (s + 0xadf) = 0x64;
            return 1;
        }
        o = func_020961a8(4);
        if (o != 0) {
            p = (Vec3 *) (o + 0x5c);
            v.x = p->x;
            v.y = p->y;
            v.z = p->z;
            if (func_020ea990(&v, s + 0x5c) > 0x8000) {
                func_020044c0(s + 0x514, 0x4ca, 0x7f, 0);
                *(u8 *) (s + 0xadd) = 0x1e;
            }
        }
    }
    if (*(u8 *) (s + 0xadd) != 0) {
        func_0203e0a8(s, 0);
        if (*(u8 *) (s + 0xadd) > 1) {
            func_020e8858(s + 0xadd);
        }
    }
    return 1;
}
