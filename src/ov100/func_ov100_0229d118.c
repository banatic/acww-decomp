/* func_ov100_0229d118 @ 0x0229d118, 0x40 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(void);
extern int func_ov100_0229d620(unsigned char *p, int q);
extern int func_ov100_0229d5d4(unsigned char *p, int q);
extern int func_ov094_0229aaac(unsigned char *p, int q);

int func_ov100_0229d118(unsigned char *p0, int p1)
{
    if (func_ov100_0229d630() != 0 || func_ov100_0229d620(p0, p1) != 0) {
        int t;
        t = func_ov100_0229d5d4(p0, p1);
        return func_ov094_0229aaac(p0 + 0xcc, t);
    } else {
        return 0x0000fff1;
    }
}
