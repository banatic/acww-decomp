/* func_ov096_0229f55c @ 0x0229f55c, 0x1e bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099fe8(void);

int func_ov096_0229f55c(void)
{
    int r0;
    r0 = func_02099fe8();
    if (r0 == -1) {
        return 0x26;
    }
    r0 = (unsigned char) r0;
    return r0;
}
