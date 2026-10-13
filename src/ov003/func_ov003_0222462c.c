/* func_ov003_0222462c @ 0x0222462c, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern void *data_ov003_0223cf70;
void func_ov003_02225b24(void *gv, void *self, Vec3 *a, Vec3 *b, int d, int e, int f);

void func_ov003_0222462c(void *self, Vec3 *p, Vec3 *q, int d, short e, short f)
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
    func_ov003_02225b24(gv, self, &a, &b, d, e, f);
}
