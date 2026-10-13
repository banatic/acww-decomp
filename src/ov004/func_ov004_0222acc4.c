/* func_ov004_0222acc4 @ 0x0222acc4, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern Vec3 data_ov004_02247774;
extern void func_020109fc(int a, int b, int c, int d);
extern int func_0203ab78(Vec3 *v);
int func_ov004_0222acc4(int a)
{
    Vec3 v;
    func_020109fc(a, 0x9b, 3, 0);
    v.x = data_ov004_02247774.x;
    v.y = data_ov004_02247774.y;
    v.z = data_ov004_02247774.z;
    return func_0203ab78(&v);
}
