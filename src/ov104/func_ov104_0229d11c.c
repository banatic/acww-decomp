/* func_ov104_0229d11c @ 0x0229d11c, 0x3c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int v);
extern void func_ov002_0220a374(void *p, int v);
extern void func_ov002_02208098(void *p, int v);

void func_ov104_0229d11c(void *self, unsigned char val)
{
    func_ov002_02207d24((char *) self + 0x23b8, 1);
    ((char *) self)[0xba] = val;
    func_ov002_0220a374((char *) self + 0x24a0, 5);
    func_ov002_02208098(self, 0x12);
}
