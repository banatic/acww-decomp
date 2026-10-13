/* func_ov137_0229c684 @ 0x0229c684, 0x60 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov137_0229c574(unsigned char *self, int n);
extern void func_ov002_0220a05c(unsigned char *ptr, int a, int b, int c, int d);
extern void func_ov002_02208098(unsigned char *self, int n);
extern void func_ov137_0229c554(unsigned char *self, int n);

void func_ov137_0229c684(unsigned char *self, int arg2, int arg3)
{
    if (func_ov137_0229c574(self, 4) != 0) {
        func_ov002_0220a05c(self + 0x94, arg2, arg3, 2, 1);
    } else {
        func_ov002_0220a05c(self + 0x94, arg2, arg3, 3, 1);
    }
    self[0x2b76] = self[0x8d];
    func_ov002_02208098(self, 8);
    func_ov137_0229c554(self, 4);
}
