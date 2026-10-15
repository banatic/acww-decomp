/* func_ov105_0229d69c @ 0x0229d69c, 0x5c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229bba4(void *p, int arg1, int arg2);
extern int func_ov094_0229bb70(void *p, int a, int b);
extern int func_ov094_0229b30c(void *p, int x);
extern int func_ov105_0229d6f8(void *self, int x);

int func_ov105_0229d69c(void *self, int a, int b, int c)
{
    int r;
    r = func_ov094_0229bba4((unsigned char *) self + 0xd5c, a, b);
    if (r == 0x37) {
        r = func_ov094_0229bb70((unsigned char *) self + 0xd5c, a, b);
    }
    if (r == 0x37) {
        goto ret_early;
    }
    if (c && func_ov094_0229b30c((unsigned char *) self + 0xd5c, r) != 0) {
        return 0x40;
    }
    return func_ov105_0229d6f8(self, r);
ret_early:
    return 0x40;
}
