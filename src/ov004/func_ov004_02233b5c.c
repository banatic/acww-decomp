/* func_ov004_02233b5c @ 0x02233b5c, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern void *data_ov004_02258ae4;
int func_ov004_02233e18(void *gv, void *self, Vec3 *a, Vec3 *b, int d, int e, int f);

void func_ov004_02233b5c(void *self, Vec3 *p, Vec3 *q, int d, short e, short f)
{
    Vec3 a, b;
    void *gv = data_ov004_02258ae4;
    if (gv == 0) {
        return;
    }
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    b.x = q->x;
    b.y = q->y;
    b.z = q->z;
    func_ov004_02233e18(gv, self, &a, &b, d, e, f);
}
