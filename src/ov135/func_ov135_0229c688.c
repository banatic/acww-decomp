/* func_ov135_0229c688 @ 0x0229c688, 0x5e bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov135_0229c574(unsigned char *self, int a);
extern int func_ov135_0229c554(unsigned char *self, int a);
extern void func_ov002_0220a05c(unsigned char *ptr, int p1, int p2, int a, int b);
extern void func_ov002_02208098(unsigned char *self, int a);

void func_ov135_0229c688(unsigned char *self, int p1, int p2)
{
    if (func_ov135_0229c574(self, 4)) {
        func_ov002_0220a05c(self + 0x98, p1, p2, 2, 1);
    } else {
        func_ov002_0220a05c(self + 0x98, p1, p2, 3, 1);
    }
    self[0x94] = self[0x8d];
    func_ov002_02208098(self, 0xa);
    func_ov135_0229c554(self, 4);
}
