/* func_ov106_0229d090 @ 0x0229d090, 0x40 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(void *a, void *b);
extern int func_ov106_0229d390(void *a, void *b);
extern int func_ov106_0229d360(void *a, void *b);
extern int func_ov094_0229b30c(void *p, int v);

int func_ov106_0229d090(void *a, void *b)
{
    if (func_ov106_0229d3a0(a, b) != 0 || func_ov106_0229d390(a, b) != 0) {
        return func_ov094_0229b30c((char *) a + 0xb58, func_ov106_0229d360(a, b));
    } else {
        return 1;
    }
}
