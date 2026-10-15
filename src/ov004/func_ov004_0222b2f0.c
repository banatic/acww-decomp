/* func_ov004_0222b2f0 @ 0x0222b2f0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222b3d4(unsigned char *addr, unsigned char *out);
extern int func_ov004_0222b3e8(unsigned char *addr, unsigned char v, int n, int arg2);

void func_ov004_0222b2f0(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_0222b3d4(base + 0x8f0, &val);
    func_ov004_0222b3e8(base, val, 6, arg2);
}
