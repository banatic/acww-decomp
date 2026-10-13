/* func_ov003_02230660 @ 0x02230660, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_ov003_02230cc0(void *a);

void func_ov003_02230660(char *self, int b, int c, int d, unsigned char e, unsigned char f)
{
    int h = func_ov003_02230cc0(self);
    func_ov003_02230ce8(self, 0, b, c, 0, h, d, 0, e, 0);
    *(char *) (self + 0x259) = f;
}
