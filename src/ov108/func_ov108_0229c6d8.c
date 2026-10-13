/* func_ov108_0229c6d8 @ 0x0229c6d8, 0x54 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(unsigned char *addr);
extern int func_ov002_02208ad8(unsigned char *addr, unsigned char b);
extern int func_ov002_0220a08c(unsigned char *addr, int a1, int a2, int a3);
extern void func_ov002_02208098(unsigned char *addr, int n);

void func_ov108_0229c6d8(unsigned char *self)
{
    int t1;
    int t2;
    t1 = func_ov002_02208ae4(self + 0x24fc);
    t2 = func_ov002_02208ad8(self + 0x24fc, self[0x2b5]);
    func_ov002_0220a08c(self + 0x2498, t1, t2, 2);
    self[0x2b3] = self[0x8d];
    func_ov002_02208098(self, 0xa);
}
