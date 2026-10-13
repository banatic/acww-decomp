/* func_020fd9a4 @ 0x020fd9a4, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;
void func_020fd9a4(int a, int b, Vec3 *v)
{
    v[0].x = b;
    v[1].x = 0;
    v[2].x = a;
    v[3].x = 0;
    v[0].y = 0;
    v[1].y = 0x1000;
    v[2].y = 0;
    v[3].y = 0;
    v[0].z = -a;
    v[1].z = 0;
    v[2].z = b;
    v[3].z = 0;
}
