/* func_ov003_0222a330 @ 0x0222a330, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
void func_0204f818(int *a, int *b, Vec3 *t);
int func_02031b5c(int a, int b);

int func_ov003_0222a330(char *self)
{
    int a, b;
    Vec3 t;
    int r = 0;
    Vec3 *p = (Vec3 *) (self + 0x120);
    t.x = p->x;
    t.y = p->y;
    t.z = p->z;
    t.z = t.z - 0x2000;
    func_0204f818(&a, &b, &t);
    if (func_02031b5c(a, b) == 1) {
        r = 1;
    }
    return r;
}
