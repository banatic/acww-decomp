/* func_ov002_0220a0b4 @ 0x0220a0b4, 0x2a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209d74(char *p);
extern void func_ov002_02209d68(char *p, int a, int b);
extern void func_ov002_0220a0e0(char *self, int a, int b);

void func_ov002_0220a0b4(char *self, int a, int b)
{
    func_ov002_02209d74(self + 0x4c);
    func_ov002_02209d68(self + 0x4c, a, b);
    func_ov002_0220a0e0(self, a, b);
}
