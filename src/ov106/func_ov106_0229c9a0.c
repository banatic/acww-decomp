/* func_ov106_0229c9a0 @ 0x0229c9a0, 0x3c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int n);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov002_02208098(void *p, int n);

void func_ov106_0229c9a0(void *self, unsigned char val)
{
    func_ov002_02207d24((char *) self + 0x21b8, 1);
    ((char *) self)[0xba] = val;
    func_ov002_0220a374((char *) self + 0x22a0, 5);
    func_ov002_02208098(self, 0x12);
}
