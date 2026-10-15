/* func_ov100_0229d67c @ 0x0229d67c, 0x1e bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099fe8(void);

int func_ov100_0229d67c(void *receiver)
{
    int r0;
    r0 = func_02099fe8();
    if (r0 == -1) {
        return 0x20;
    }
    return (unsigned char) r0;
}
