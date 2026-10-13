/* func_0202ffbc @ 0x0202ffbc, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern void func_0202ff68(int, Vec3 *);
extern void func_020ea9e4(Vec3 *, int);

void func_0202ffbc(int a, Vec3 *out, int b)
{
    Vec3 local;
    func_0202ff68(a, &local);
    out->x = local.x;
    out->y = local.y;
    out->z = local.z;
    func_020ea9e4(&local, b);
}
