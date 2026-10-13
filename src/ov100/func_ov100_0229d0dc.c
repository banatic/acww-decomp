/* func_ov100_0229d0dc @ 0x0229d0dc, 0x3a bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(void *p0, int p1);
extern int func_ov100_0229d620(void *p0, int p1);
extern int func_ov100_0229d5d4(void *p0, int p1);
extern int func_ov094_0229aa84(void *ptr, int val);

int func_ov100_0229d0dc(void *p0, int p1)
{
    if (func_ov100_0229d630(p0, p1) || func_ov100_0229d620(p0, p1)) {
        return func_ov094_0229aa84((char *) p0 + 0xcc, func_ov100_0229d5d4(p0, p1));
    }
    return 0xf1;
}
