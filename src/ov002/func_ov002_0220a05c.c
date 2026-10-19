/* func_ov002_0220a05c @ 0x0220a05c, 0x2e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int cmd);
extern void func_ov002_02209d08(char *p, int a, int b, int c);

void func_ov002_0220a05c(char *self, int a, int b, int c, int flag)
{
    if (flag) {
        func_0200467c(0xb);
    }
    self += 0x4c;
    func_ov002_02209d08(self, a, b, c);
}
