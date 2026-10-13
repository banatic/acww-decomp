/* func_ov003_0222799c @ 0x0222799c, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

int func_ov003_0222799c(Vec3 *a, Vec3 *b, int dx, int dz, int dz2)
{
    int r = 0;
    int d, e, f;
    d = b->x - a->x;
    if (d < 0) {
        d = -d;
    }
    if (d > dx) {
        return 0;
    }
    e = b->z - a->z;
    if (e >= 0) {
        if (e <= dz) {
            r = 1;
        }
    } else {
        f = a->z - b->z;
        if (f <= dz2) {
            r = 1;
        }
    }
    return r;
}
