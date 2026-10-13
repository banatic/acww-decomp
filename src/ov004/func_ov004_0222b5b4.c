/* func_ov004_0222b5b4 @ 0x0222b5b4, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222b694(unsigned char *addr, unsigned char *out);
extern void func_ov004_0222b6a8(unsigned char *addr, unsigned char v, int n, int arg2);

void func_ov004_0222b5b4(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_0222b694(base + 0x8f0, &val);
    func_ov004_0222b6a8(base, val, 6, arg2);
}
