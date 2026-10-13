/* func_ov107_0229cd1c @ 0x0229cd1c, 0x4c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);

void func_ov107_0229cd1c(unsigned char *self)
{
    int a, b;
    self[0xbd] = 0;
    a = func_ov002_02208ae4(self + 0x2318);
    b = func_ov002_02208ad8(self + 0x2318, self[0xbd]);
    func_ov002_0220a0b4(self + 0x22b4, a, b);
    func_ov002_0220a374(self + 0x22b4, 7);
}
