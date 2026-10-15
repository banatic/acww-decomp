/* func_ov003_02224678 @ 0x02224678, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern void *data_ov003_0223cf70;
int func_ov003_02225da0(void *gv, void *self, Vec3 *a, int k, Vec3 *b, int d, int e, int f);

void func_ov003_02224678(void *self, Vec3 *p, Vec3 *q, int d, short e, short f)
{
    Vec3 a, b;
    void *gv = data_ov003_0223cf70;
    if (gv == 0) {
        return;
    }
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    b.x = q->x;
    b.y = q->y;
    b.z = q->z;
    func_ov003_02225da0(gv, self, &a, 0x1f, &b, d, e, f);
}
