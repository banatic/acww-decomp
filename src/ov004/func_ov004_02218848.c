/* func_ov004_02218848 @ 0x02218848, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern Vec3 *func_ov004_0223cb24(void *k);
extern int func_ov004_0223cb2c(void *k);
extern int func_ov004_0223cb18(void *k);
extern void func_020ea6e0(Vec3 *out, int a);
extern void VEC_Add(Vec3 *d, Vec3 *a, Vec3 *b);

void func_ov004_02218848(char *self, Vec3 *out, void *k)
{
    Vec3 v;
    Vec3 *p;
    int z;
    if (*(int *) (self + 0x784) == 0) {
        out->x = *(int *) (self + 0x5c);
        out->y = *(int *) (self + 0x60);
        out->z = *(int *) (self + 0x64);
    } else {
        p = func_ov004_0223cb24(k);
        out->x = p->x;
        out->y = p->y;
        out->z = p->z;
        z = func_ov004_0223cb2c(k) + 0x1000;
        v.x = 0;
        v.y = 0;
        v.z = z;
        func_020ea6e0(&v, func_ov004_0223cb18(k));
        VEC_Add(out, &v, out);
    }
}
