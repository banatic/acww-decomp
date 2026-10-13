/* func_ov003_0222796c @ 0x0222796c, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
int func_ov003_02227950(int a, int b, int c);

int func_ov003_0222796c(Vec3 *a, Vec3 *b, Vec3 *c)
{
    if (func_ov003_02227950(a->x, b->x, c->x) != 0 && func_ov003_02227950(a->z, b->z, c->z) != 0) {
        return 1;
    }
    return 0;
}
