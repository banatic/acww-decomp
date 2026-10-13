/* func_ov108_0229c674 @ 0x0229c674, 0x64 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022090e4(void *ptr);
extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char val);
extern void func_ov002_0220a0b4(void *ptr, int arg1, int arg2);
extern void func_0208e4c0(void *ptr, int arg);
extern void func_ov002_02208098(void *ptr, int arg);

void func_ov108_0229c674(unsigned char *self)
{
    int x;

    self[0x2B4] = 1;
    self[0x2B5] = (unsigned char) func_ov002_022090e4(self + 0x24FC);
    x = func_ov002_02208ae4(self + 0x24FC);
    func_ov002_0220a0b4(self + 0x2498, x, func_ov002_02208ad8(self + 0x24FC, self[0x2B5]));
    func_0208e4c0(self + 0x2498, 8);
    func_ov002_02208098(self, 0x14);
}
