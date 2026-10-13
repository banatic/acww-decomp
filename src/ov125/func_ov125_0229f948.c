/* func_ov125_0229f948 @ 0x0229f948, 0x4c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, int b);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int c);

void func_ov125_0229f948(unsigned char *self)
{
    int a, b;

    self[0x87e] = 0;
    a = func_ov002_02208ae4(self + 0x180);
    b = func_ov002_02208ad8(self + 0x180, self[0x87e]);
    func_ov002_0220a0b4(self + 0x644, a, b);
    func_ov002_0220a374(self + 0x644, 7);
}
