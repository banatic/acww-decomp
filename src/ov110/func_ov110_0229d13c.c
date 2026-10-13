/* func_ov110_0229d13c @ 0x0229d13c, 0x40 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(char *a, void *b);
extern int func_ov110_0229d5d4(char *a, void *b);
extern int func_ov110_0229d590(char *a, void *b);
extern int func_ov094_0229a8bc(char *a, int b);

int func_ov110_0229d13c(char *a, void *b)
{
    if (func_ov110_0229d5e4(a, b) != 0 || func_ov110_0229d5d4(a, b) != 0) {
        return func_ov094_0229a8bc(a + 0x138, func_ov110_0229d590(a, b));
    }
    return 0;
}
