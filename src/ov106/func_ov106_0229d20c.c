/* func_ov106_0229d20c @ 0x0229d20c, 0x40 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(char *a, char *b);
extern int func_ov106_0229d390(char *a, char *b);
extern int func_ov106_0229d360(char *a, char *b);
extern int func_ov094_0229b8d8(char *addr, int value);

int func_ov106_0229d20c(char *a, char *b)
{
    if (func_ov106_0229d3a0(a, b) != 0 || func_ov106_0229d390(a, b) != 0) {
        return func_ov094_0229b8d8(a + 0xb58, func_ov106_0229d360(a, b));
    } else {
        return 0;
    }
}
