/* func_ov004_02228318 @ 0x02228318, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022283bc(unsigned char *addr, unsigned char *out);
extern void func_ov004_022283cc(unsigned char *addr, unsigned char v, int n, int arg2);

void func_ov004_02228318(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_022283bc(base + 0x8f0, &val);
    func_ov004_022283cc(base, val, 6, arg2);
}
