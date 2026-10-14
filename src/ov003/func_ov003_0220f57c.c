/* func_ov003_0220f57c @ 0x0220f57c, 0x12 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

void func_ov003_0220f57c(int *out, Vec v)
{
    out[0] = v.x;
    out[1] = v.y;
    out[2] = v.z;
}
