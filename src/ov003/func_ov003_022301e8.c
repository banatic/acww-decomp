/* func_ov003_022301e8 @ 0x022301e8, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_02056fcc(void *a, int b, int c, int d, int e);

void func_ov003_022301e8(char *self)
{
    func_ov003_02230ce8(self, 0, 0x64, 0x50, 0, 0, 0, 0, 5, 0);
    *(char *) (self + 0x24c) = 0;
    func_02056fcc(self + 0xec, 3, 0, 0x1000, 0);
}
