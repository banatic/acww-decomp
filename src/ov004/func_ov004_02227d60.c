/* func_ov004_02227d60 @ 0x02227d60, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200fbc4(char *self, int a, int b, int c);
int func_ov004_02227d60(char *self)
{
    char *p = self + 0x7d4;
    return func_0200fbc4(self, *(int *) (p + 8), *(int *) (p + 0xc), *(short *) (p + 4));
}
