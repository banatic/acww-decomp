/* func_02031650 @ 0x02031650, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern int _u32_div_f(void *arr, unsigned int count);
extern void func_020ea6e0(int *v, int angle);
extern int FX_MulFunc(int a, int b);
extern int func_020316fc(Vec3 *a, int d, int *out, int p3);

int func_02031650(Vec3 *out, Vec3 *base, void *arr, int p4, unsigned int count, int p6, int p7)
{
    int scale;
    int ry;
    int rz;
    int t;
    int local;
    Vec3 vec;
    Vec3 result;
    int i;

    if (count >= 1) {
        scale = _u32_div_f(arr, count);
        vec.x = 0;
        vec.y = 0;
        vec.z = 0x1000;
        func_020ea6e0((int *) &vec, p4);
        for (i = 0; i <= count; i++) {
            t = i * scale;
            rz = base->z + FX_MulFunc(vec.z, t);
            ry = base->y + FX_MulFunc(vec.y, t);
            result.x = base->x + FX_MulFunc(vec.x, t);
            result.y = ry;
            result.z = rz;
            if (func_020316fc(&result, p6, &local, p7) != 0) {
                out->x = result.x;
                out->y = result.y;
                out->z = result.z;
                out->y = local;
                return 1;
            }
        }
    }
    return 0;
}
