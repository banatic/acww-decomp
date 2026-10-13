/* func_ov123_02299ec4 @ 0x02299ec4, 0x44 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O1,s
 */

extern struct {
    unsigned char pad[2];
    unsigned short field;
} data_ov123_0229cf20;
void func_ov123_02299630(int, int);

void func_ov123_02299ec4(int a)
{
    unsigned short v;
    unsigned int t;
    unsigned int acc;

    func_ov123_02299630(a, 0x100);
    v = data_ov123_0229cf20.field;
    acc = v & 0xffffc1ff;
    t = (unsigned short) ((((unsigned) v << 18) >> 27) & ~0x18);
    t = (unsigned short) (t | 8);
    t &= 0x1f;
    data_ov123_0229cf20.field = acc | (t << 9);
}
