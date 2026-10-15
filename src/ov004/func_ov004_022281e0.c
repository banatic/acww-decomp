/* func_ov004_022281e0 @ 0x022281e0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022282b0(unsigned char *addr, unsigned char *out);
extern int func_ov004_022282c0(unsigned char *addr, unsigned char v, int n, int arg2);

void func_ov004_022281e0(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_022282b0(base + 0x8f0, &val);
    func_ov004_022282c0(base, val, 6, arg2);
}
