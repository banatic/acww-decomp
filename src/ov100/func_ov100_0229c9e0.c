/* func_ov100_0229c9e0 @ 0x0229c9e0, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int n);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov002_02208098(void *p, int n);

void func_ov100_0229c9e0(void *self, unsigned char val)
{
    func_ov002_02207d24((char *) self + 0x218c, 1);
    ((unsigned char *) self)[0x2923] = val;
    func_ov002_0220a374((char *) self + 0x2274, 5);
    func_ov002_02208098(self, 0xd);
}
