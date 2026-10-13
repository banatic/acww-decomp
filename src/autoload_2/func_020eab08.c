/* func_020eab08 @ 0x020eab08, 0xc0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int FX_Div(int, int);

void func_020eab08(int *v, int scale)
{
    if (scale == 0) {
        if (v[0] > 0) {
            v[0] = 0x7fffffff;
        } else if (v[0] < 0) {
            v[0] = -0x80000000;
        }

        if (v[1] > 0) {
            v[1] = 0x7fffffff;
        } else if (v[1] < 0) {
            v[1] = -0x80000000;
        }

        if (v[2] > 0) {
            v[2] = 0x7fffffff;
            return;
        }
        if (v[2] < 0) {
            v[2] = -0x80000000;
        }
    } else {
        v[0] = FX_Div(v[0], scale);
        v[1] = FX_Div(v[1], scale);
        v[2] = FX_Div(v[2], scale);
    }
}
