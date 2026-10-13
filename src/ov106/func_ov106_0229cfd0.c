/* func_ov106_0229cfd0 @ 0x0229cfd0, 0x3c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(char *p, char *q);
extern int func_ov106_0229d390(char *p, char *q);
extern int func_ov106_0229d360(char *p, char *q);
extern void func_ov094_0229b938(char *p, int v);

void func_ov106_0229cfd0(char *p, char *q)
{
    if (func_ov106_0229d3a0(p, q) != 0 || func_ov106_0229d390(p, q) != 0) {
        func_ov094_0229b938(p + 0xb58, func_ov106_0229d360(p, q));
    }
}
