/* func_ov110_0229d628 @ 0x0229d628, 0x1e bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099fe8(void);

unsigned char func_ov110_0229d628(void)
{
    int result = func_02099fe8();
    if (result == -1) {
        return 31;
    }
    return (unsigned char) result;
}
