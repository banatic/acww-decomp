/* func_ov129_0229cf5c @ 0x0229cf5c, 0x6c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_02299b78(unsigned char *p);
extern unsigned char func_ov127_02299d20(unsigned char *p, unsigned char a, unsigned char b);
extern void func_ov127_02299c08(unsigned char *p, unsigned char a, int b);
extern void func_ov002_02208098(unsigned char *p, int v);
extern unsigned char data_021fbdd8, data_021f6c60, data_021f6c5c;

void func_ov129_0229cf5c(unsigned char *self)
{
    if (func_ov127_02299b78(self + 0x734) == 0) {
        return;
    }
    if (data_021fbdd8 != 0) {
        self[0xad] = func_ov127_02299d20(self + 0x734, data_021f6c60, data_021f6c5c);
        if (self[0xad] != 4) {
            func_ov127_02299c08(self + 0x734, self[0xad], 0);
            func_ov002_02208098(self, 1);
            return;
        }
    }
    func_ov002_02208098(self, 0);
}
