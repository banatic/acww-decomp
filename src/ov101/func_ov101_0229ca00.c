/* func_ov101_0229ca00 @ 0x0229ca00, 0x2c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);

void func_ov101_0229ca00(char *p)
{
    *(int *) (p + 0xa4) = func_ov002_02209f3c(p + 0x229c) - 2;
    *(int *) (p + 0xa8) = func_ov002_02209f14(p + 0x229c) - 4;
}
