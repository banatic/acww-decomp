/* func_ov096_0229ee50 @ 0x0229ee50, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229e4f8(void);

int func_ov096_0229ee50(int r0, int r1)
{
    if (r1 == 0) {
        return 1;
    }
    if (r1 == 2) {
        return 0;
    }
    if (r1 == 1) {
        if (func_ov096_0229e4f8() == 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}
