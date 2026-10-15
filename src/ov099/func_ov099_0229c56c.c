/* func_ov099_0229c56c @ 0x0229c56c, 0x3c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *p, int v);
extern void func_ov002_0220a374(void *p, int v);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov099_0229c56c(void *self, unsigned char val)
{
    func_ov002_02207d24((char *) self + 0x218c, 1);
    ((char *) self)[0x2909] = val;
    func_ov002_0220a374((char *) self + 0x2274, 5);
    func_ov002_02208098(self, 0xd);
}
