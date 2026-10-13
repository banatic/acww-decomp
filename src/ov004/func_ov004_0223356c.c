/* func_ov004_0223356c @ 0x0223356c, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b;
} UnkStruct_0223356c;
extern int func_ov004_0223362c(void *, void *, UnkStruct_0223356c *, Vec3 *, Vec3 *, int, void *, int, u8);
extern char data_ov004_02258af4;

int func_ov004_0223356c(void *self, void *p2, Vec3 *a, Vec3 *b, u8 p5)
{
    UnkStruct_0223356c p;
    Vec3 v1, v2;
    v1.x = a->x;
    v1.y = a->y;
    v1.z = a->z;
    v2.x = b->x;
    v2.y = b->y;
    v2.z = b->z;
    p.a = 0;
    p.b = 0;
    return func_ov004_0223362c(&data_ov004_02258af4, self, &p, &v1, &v2, 0, p2, 0, p5);
}
