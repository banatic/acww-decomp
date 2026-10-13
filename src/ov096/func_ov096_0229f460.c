/* func_ov096_0229f460 @ 0x0229f460, 0x1c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f460(int r0, int r1, int r2);

int func_ov096_0229f460(int r0, int r1, int r2)
{
    if (r1 < 4 || r1 >= 0x1c) {
        return 0;
    }
    if (r2 < 0xac || r2 >= 0xc4) {
        return 0;
    }
    return 1;
}
