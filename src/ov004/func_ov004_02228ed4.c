/* func_ov004_02228ed4 @ 0x02228ed4, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020110a0(void *self, const int *p);

int func_ov004_02228ed4(char *self)
{
    const int *src = (const int *) (self + 0x7d4);
    int *dst = (int *) (self + 0x5c);
    dst[0] = src[0];
    dst[2] = src[1];
    return func_020110a0(self, src + 2);
}
