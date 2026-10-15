/* func_0205c1a4 @ 0x0205c1a4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020952e4(void);
extern unsigned int func_020952e0(void);
extern unsigned int GX_ResetBankForSubOBJExtPltt(unsigned int, unsigned int);
extern unsigned int data_021c9ab4;

void func_0205c1a4(unsigned int arg)
{
    unsigned int len = 0;
    unsigned int total = len;
    unsigned int extra;

    len += (func_020952e4() + 3) & ~3;
    extra = func_020952e0();
    extra = ~(extra - 1) & (extra + 15);
    total += (len + extra) << 2;
    data_021c9ab4 = GX_ResetBankForSubOBJExtPltt(total, arg);
}
