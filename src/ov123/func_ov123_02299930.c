/* func_ov123_02299930 @ 0x02299930, 0x22 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_02299650(int, int);
extern void func_ov123_02299630(int, int);
extern void func_0200277c(int);

void func_ov123_02299930(int param)
{
    if (func_ov123_02299650(param, 32) != 0) {
        func_ov123_02299630(param, 32);
        func_0200277c(3);
    }
}
