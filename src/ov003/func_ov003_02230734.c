/* func_ov003_02230734 @ 0x02230734, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_ov003_02230cc0(void);
extern int func_020644cc(int a);

void func_ov003_02230734(char *self, int b, int c, int d, unsigned char e)
{
    int h = func_ov003_02230cc0();
    func_ov003_02230ce8(self, 0x3b6, b, c, 0, h, 0, 0, d, 0);
    *(short *) (self + 0x232) = (short) (0x14 * (func_020644cc(9) + 2));
    *(char *) (self + 0x259) = e;
    *(int *) (self + 0x208) = 0;
}
