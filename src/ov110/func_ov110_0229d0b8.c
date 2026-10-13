/* func_ov110_0229d0b8 @ 0x0229d0b8, 0x44 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(int a, int b);
extern int func_ov110_0229d5d4(int a, int b);
extern int func_ov110_0229d590(int a, int b);
extern int func_ov094_0229aaac(char *addr, int value);

int func_ov110_0229d0b8(int a, int b)
{
    if (func_ov110_0229d5e4(a, b) != 0 || func_ov110_0229d5d4(a, b) != 0) {
        return func_ov094_0229aaac((char *) a + 0x138, func_ov110_0229d590(a, b));
    }
    return 0xfff1;
}
