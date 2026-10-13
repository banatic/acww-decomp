/* func_ov123_02299954 @ 0x02299954, 0x2c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_02299650(int, int);
extern int func_ov123_02299640(int, int);
extern void func_02002708(int);
extern void func_02001a04(int, int, int);

void func_ov123_02299954(int param)
{
    if (func_ov123_02299650(param, 0x20) == 0) {
        func_ov123_02299640(param, 0x20);
        func_02002708(3);
        func_02001a04(1, 8, 0xc);
    }
}
