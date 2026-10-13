/* func_ov004_0222b468 @ 0x0222b468, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222b4d4(unsigned char *addr, unsigned char *out);
extern void func_ov004_0222b4e0(unsigned char *addr, unsigned char v, int n, int arg2);

void func_ov004_0222b468(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_0222b4d4(base + 0x8f0, &val);
    func_ov004_0222b4e0(base, val, 6, arg2);
}
