/* func_ov004_022210fc @ 0x022210fc, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02220318(void *self);
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern void func_ov004_02221550(void *self, int k);
int func_ov004_022210fc(unsigned char *self)
{
    if (func_ov004_02220318(self) != 0) {
        return 1;
    }
    if (func_02019e00(self + 0x564) == 3) {
        if (func_02019de8(self + 0x564) != 0) {
            func_ov004_02221550(self, 3);
        }
    }
    return 1;
}
