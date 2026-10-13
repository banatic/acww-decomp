/* func_ov108_0229c940 @ 0x0229c940, 0x2c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(char *addr);
extern int func_ov002_02209f14(char *addr);

void func_ov108_0229c940(char *p)
{
    int res1, res2;
    res1 = func_ov002_02209f3c(p + 0x2498) - 2;
    *(int *) (p + 0xa4) = res1;
    res2 = func_ov002_02209f14(p + 0x2498) - 4;
    *(int *) (p + 0xa8) = res2;
}
