/* func_ov101_0229c624 @ 0x0229c624, 0x3c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *ptr, int value);
extern void func_ov002_0220a374(void *ptr, int value);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);

void func_ov101_0229c624(void *self, unsigned char value)
{
    func_ov002_02207d24((char *) self + 0x21b4, 1);
    ((char *) self)[0xb5] = value;
    func_ov002_0220a374((char *) self + 0x229c, 5);
    func_ov002_02208098(self, 0xf);
}
