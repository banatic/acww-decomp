/* func_ov004_0222c2f8 @ 0x0222c2f8, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern int func_020044d0(void *a, Vec3 *v);
int func_ov004_0222c2f8(void *a, Vec3 *src)
{
    Vec3 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;
    return func_020044d0(a, &v);
}
