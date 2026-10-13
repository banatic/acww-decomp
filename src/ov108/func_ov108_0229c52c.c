/* func_ov108_0229c52c @ 0x0229c52c, 0x4c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int n);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov002_02208098(void *p, int n);

void func_ov108_0229c52c(unsigned char *self, unsigned char param)
{
    unsigned char b;
    func_ov002_02207d24(self + 0x23b0, 1);
    b = self[0x8d];
    self[0x2b3] = b;
    self[0x2b2] = param;
    func_ov002_0220a374(self + 0x2498, 6);
    func_ov002_02208098(self, 16);
}
