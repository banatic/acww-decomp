/* func_ov003_022305bc @ 0x022305bc, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_ov003_02230f88(void *a);
extern int func_020644cc(int a);

void func_ov003_022305bc(char *self)
{
    func_ov003_02230ce8(self, 0, 0x28, 0x50, 0, 0, 0, 0, 3, 1);
    func_ov003_02230f88(self);
    *(short *) (self + 0x232) = (short) (3 * func_020644cc(0x14));
}
