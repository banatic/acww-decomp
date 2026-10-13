/* func_ov003_02224718 @ 0x02224718, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
int func_02046730(Vec3 *out);
void func_020eaca0(Vec3 *out, Vec3 *a, void *b);

int func_ov003_02224718(Vec3 *out, void *b)
{
    volatile Vec3 u;
    Vec3 t;
    int r;
    out->x = 0;
    out->y = 0;
    out->z = 0;
    r = func_02046730(out);
    if (r != 0) {
        func_020eaca0(&t, out, b);
        u.x = t.x;
        u.y = t.y;
        u.z = t.z;
        if (t.x * t.x + t.z * t.z < (int) 0x90000000) {
            r = 1;
        }
    }
    return r;
}
