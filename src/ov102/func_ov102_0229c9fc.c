/* func_ov102_0229c9fc @ 0x0229c9fc, 0x3c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int v);
extern void func_ov002_0220a374(void *p, int v);
extern void func_ov002_02208098(void *p, int v);

void func_ov102_0229c9fc(void *self, unsigned char value)
{
    func_ov002_02207d24((char *) self + 0x218c, 1);
    ((unsigned char *) self)[0x25a6] = value;
    func_ov002_0220a374((char *) self + 0x2274, 5);
    func_ov002_02208098(self, 0xa);
}
