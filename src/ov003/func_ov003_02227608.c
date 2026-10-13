/* func_ov003_02227608 @ 0x02227608, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
void *func_ov003_02227654(int i);
int func_ov003_02227608(Vec3 *dst, int i)
{
    Vec3 *q;
    void *e = func_ov003_02227654(i);
    if (e == 0) {
        return 0;
    }
    q = (Vec3 *) ((char *) e + 0x120);
    dst->x = q->x;
    dst->y = q->y;
    dst->z = q->z;
    return 1;
}
