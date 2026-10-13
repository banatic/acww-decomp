/* func_ov107_0229d0f0 @ 0x0229d0f0, 0x38 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(void *p0, void *p1);
extern int func_ov107_0229d36c(void *p0, void *p1);
extern int func_ov094_0229aaac(void *p0, int p1);

int func_ov107_0229d0f0(void *p0, void *p1)
{
    if (func_ov107_0229d388(p0, p1)) {
        int t = func_ov107_0229d36c(p0, p1);
        return func_ov094_0229aaac((char *) p0 + 0x10c, t);
    } else {
        return 0xfff1;
    }
}
