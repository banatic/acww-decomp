/* func_ov003_022321b8 @ 0x022321b8, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int num, int den);

void func_ov003_022321b8(int *dst, const int *src, int t)
{
    int m = FX_Div(t << 12, 0x40000);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[1] = 0;
    if (src[0] >= 0) {
        if (src[0] > m) {
            dst[0] = m;
        }
    } else if (src[0] < -m) {
        dst[0] = -m;
    }
    if (src[2] >= 0) {
        if (src[2] > m) {
            dst[2] = m;
        }
    } else if (src[2] < -m) {
        dst[2] = -m;
    }
}
