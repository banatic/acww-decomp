/* func_ov106_0229d028 @ 0x0229d028, 0x4c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(char *p1, int p2);
extern int func_ov106_0229d390(char *p1, int p2);
extern int func_ov106_0229d360(char *p1, int p2);
extern void func_ov106_0229d074(char *p1);
extern void func_ov094_0229b950(char *addr, int val);
extern void func_ov094_0229ab5c(char *addr);

void func_ov106_0229d028(char *p1, int p2)
{
    if (func_ov106_0229d3a0(p1, p2) != 0 || func_ov106_0229d390(p1, p2) != 0) {
        int tmp;
        tmp = func_ov106_0229d360(p1, p2);
        func_ov094_0229b950(p1 + 0xb58, tmp);
        func_ov094_0229ab5c(p1 + 0xf8);
    } else {
        func_ov106_0229d074(p1);
    }
}
