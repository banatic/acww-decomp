/* func_ov003_02225714 @ 0x02225714, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} UnkStruct_02225714;

extern char *func_ov003_02225768(void *a, void *b, void *c, int d, Vec3 *v, UnkStruct_02225714 m);
extern int func_0204b7a0(void *b);
extern void func_020ad238(Vec3 *v, u8 k);

void func_ov003_02225714(void *a, void *b, void *c, int d, Vec3 *v, UnkStruct_02225714 m)
{
    Vec3 t;
    t.x = v->x;
    t.y = v->y;
    t.z = v->z;
    func_ov003_02225768(a, b, c, d, &t, m);
    func_020ad238(v, (u8) func_0204b7a0(b));
}
