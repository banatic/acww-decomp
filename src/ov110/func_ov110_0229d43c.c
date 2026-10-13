/* func_ov110_0229d43c @ 0x0229d43c, 0x1a bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5d4(void);

int func_ov110_0229d43c(int param1, int param2)
{
    int result;
    if (func_ov110_0229d5d4() != 0) {
        result = (unsigned char) param2;
    } else {
        result = 0xf;
    }
    return result;
}
