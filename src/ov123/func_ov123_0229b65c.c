/* func_ov123_0229b65c @ 0x0229b65c, 0x20 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov123_0229b6d0(int);
extern void func_ov123_0229b67c(int);

void func_ov123_0229b65c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov123_0229b6d0(r4);
    } else {
        func_ov123_0229b67c(r4);
    }
}
