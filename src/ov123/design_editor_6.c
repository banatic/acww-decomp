/* design_editor_6: 2 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229b33c @ 0x0229b33c, 0x28 bytes, Thumb
 * func_ov123_0229b308 @ 0x0229b308, 0x34 bytes, Thumb
 */

extern int func_02002a88(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int func_020b9c10(int a, int b, int c, int d, int e, int f);

int func_ov123_0229b33c(unsigned int p)
{
    return func_02002a88(p + 0x2e30, 6, 0x120, 0x120, 0x12f);
}

void func_ov123_0229b308(void *p)
{
    func_020b9c10((int) p + 0x124, (int) p + 0x2e30, 6, 0x120, 0x120, 0x12f);
}
