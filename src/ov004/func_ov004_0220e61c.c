/* func_ov004_0220e61c @ 0x0220e61c, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern int func_02091230(int a, Vec3 *v, int c, int d);
int func_ov004_0220e61c(void *self, Vec3 *src)
{
    Vec3 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;
    return func_02091230(0x3d, &v, 0, 0);
}
