/* func_ov101_0229cc80 @ 0x0229cc80, 0x4e bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0206f9cc(char *a);
extern int func_ov101_0229cc20(char *a, unsigned char i);
extern int func_ov101_0229ce1c(char *a, unsigned char i);
extern void func_ov094_0229a888(char *p, int v);

void func_ov101_0229cc80(char *a)
{
    unsigned char i;
    int b;
    unsigned int mask;
    int ret;

    mask = func_0206f9cc(a);
    for (i = 0, b = 0; i <= 14; i++, b++) {
        if (func_ov101_0229cc20(a, i) != 0) {
            continue;
        }
        if (mask & (1 << b)) {
            continue;
        }
        ret = func_ov101_0229ce1c(a, i);
        func_ov094_0229a888(a + 0xf4, ret);
    }
}
