/* func_ov104_0229d2b4 @ 0x0229d2b4, 0x50 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern void func_ov002_0220a08c(void *p, int a, int b, int c);
extern void func_ov002_02208098(void *p, int v);

void func_ov104_0229d2b4(unsigned char *self)
{
    int a = func_ov002_02208ae4(self + 0x2504);
    int b = func_ov002_02208ad8(self + 0x2504, *(unsigned char *) (self + 0xbd));
    func_ov002_0220a08c(self + 0x24a0, a, b, 2);
    *(unsigned char *) (self + 0xbb) = *(unsigned char *) (self + 0x8d);
    func_ov002_02208098(self, 13);
}
