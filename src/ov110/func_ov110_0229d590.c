/* func_ov110_0229d590 @ 0x0229d590, 0x36 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(int unused0, unsigned int unused1);
extern int func_ov110_0229d5d4(int, int);
extern int func_ov110_0229d43c(int, int);

int func_ov110_0229d590(int a, int b)
{
    int result;
    if (func_ov110_0229d5e4(a, b) != 0) {
        result = (unsigned char) b;
    } else {
        if (func_ov110_0229d5d4(a, b) != 0) {
            result = func_ov110_0229d43c(a, b);
        } else {
            result = 0;
        }
    }
    return result;
}
