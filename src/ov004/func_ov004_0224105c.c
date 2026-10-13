/* func_ov004_0224105c @ 0x0224105c, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int a);
extern int FX_MulFunc(int a, int b);
short func_ov004_0224105c(int x)
{
    return (short) FX_MulFunc(0x38e, (func_020644cc(x * 2 + 1) - x) << 12);
}
