/* func_ov123_0229a2b4 @ 0x0229a2b4, 0x44 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_02299650(void *p, int n);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_ov123_02299630(void *p, int n);

void func_ov123_0229a2b4(char *p)
{
    if (func_ov123_02299650(p, 0x10) == 0) {
        return;
    }
    if (func_020b9bbc(p + 0x194, p + 0x230, 6, 0x800, 0) != 0) {
        func_ov123_02299630(p, 0x10);
    }
}
