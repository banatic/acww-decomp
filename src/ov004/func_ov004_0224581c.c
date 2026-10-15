/* func_ov004_0224581c @ 0x0224581c, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern Vec3 *func_02095794(int);
extern int func_02095ab0(Vec3 *, int, int);

void func_ov004_0224581c(void)
{
    Vec3 *s = func_02095794(4);
    Vec3 v;
    v.x = s->x;
    v.y = s->y;
    v.z = s->z;
    v.z += 0x6000;
    func_02095ab0(&v, 0x2b8, 4);
}
