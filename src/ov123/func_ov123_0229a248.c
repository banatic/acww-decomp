/* func_ov123_0229a248 @ 0x0229a248, 0x2e bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_0229a224(void *, unsigned char);
extern void func_ov123_0229a2f8(void *, unsigned char, int);

void func_ov123_0229a248(unsigned char *this, unsigned char val)
{
    func_ov123_0229a224(this, val);
    this[0xA6] = val;
    this[0xA7] = 4;
    func_ov123_0229a2f8(this, this[0xA6], 5);
}
