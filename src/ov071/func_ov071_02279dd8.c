/* func_ov071_02279dd8 @ 0x02279dd8, 0x58 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(int);
extern void func_02016764(int, int, int, int, int, int, int, int);
extern void func_02054188(int, int, int);
extern void func_ov071_02279d04(int, int);

int func_ov071_02279dd8(int self)
{
    if (!func_0202ec58(self)) {
        return 0;
    }

    func_02016764(self + 0x334, self, 0x141, 0, 0, 0x1000, 0, 1);
    func_02054188(self + 0xec, 0xc, 0xe);
    func_ov071_02279d04(self, 4);
    return 1;
}
