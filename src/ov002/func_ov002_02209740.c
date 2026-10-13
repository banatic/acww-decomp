/* func_ov002_02209740 @ 0x02209740, 0x2e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208b74(void *self, int *px);
extern void func_ov002_02209954(void *self, int x, int y);
extern void func_ov002_0220970c(void *self, int y);

void func_ov002_02209740(void *self, int x, int y)
{
    func_ov002_02208b74(self, &x);
    func_ov002_02209954(self, 0, -0xc);
    func_ov002_0220970c(self, y);
}
