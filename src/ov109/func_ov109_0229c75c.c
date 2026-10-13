/* func_ov109_0229c75c @ 0x0229c75c, 0x54 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(const unsigned char *p);
extern int func_ov002_02208ad8(const unsigned char *p, int b);
extern void func_ov002_0220a08c(const unsigned char *p, int a, int b, int c);
extern void func_ov002_02208098(const unsigned char *p, int n);

void func_ov109_0229c75c(unsigned char *self)
{
    int v1, v2;

    v1 = func_ov002_02208ae4(self + 0x22d8);
    v2 = func_ov002_02208ad8(self + 0x22d8, self[0x29d8]);
    func_ov002_0220a08c(self + 0x2274, v1, v2, 2);
    self[0x29d6] = self[0x8d];
    func_ov002_02208098(self, 8);
}
