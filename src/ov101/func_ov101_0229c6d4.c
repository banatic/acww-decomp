/* func_ov101_0229c6d4 @ 0x0229c6d4, 0x4c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int val);

void func_ov101_0229c6d4(unsigned char *self)
{
    int a, b;

    self[0xb8] = 0;
    a = func_ov002_02208ae4(self + 0x2300);
    b = func_ov002_02208ad8(self + 0x2300, self[0xb8]);
    func_ov002_0220a0b4(self + 0x229c, a, b);
    func_ov002_0220a374(self + 0x229c, 7);
}
