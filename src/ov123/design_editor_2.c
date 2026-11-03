/* design_editor_2: 3 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_02299980 @ 0x02299980, 0x2e bytes, Thumb
 * func_ov123_02299954 @ 0x02299954, 0x2c bytes, Thumb
 * func_ov123_02299930 @ 0x02299930, 0x22 bytes, Thumb
 */

extern int func_ov123_02299650(int a, int b);
extern void func_0200467c(int cmd);
extern void func_ov123_02299640(int, int);
extern void func_02002708(int);
extern void func_02001a04(int, int, int);
extern void func_ov123_02299630(int, int);
extern void func_0200277c(int);

void func_ov123_02299954(int param);
void func_ov123_02299930(int param);

void func_ov123_02299980(int a)
{
    if (func_ov123_02299650(a, 0x20) != 0) {
        func_ov123_02299930(a);
        func_0200467c(0x42);
    } else {
        func_ov123_02299954(a);
        func_0200467c(0x41);
    }
}

void func_ov123_02299954(int param)
{
    if (func_ov123_02299650(param, 0x20) == 0) {
        func_ov123_02299640(param, 0x20);
        func_02002708(3);
        func_02001a04(1, 8, 0xc);
    }
}

void func_ov123_02299930(int param)
{
    if (func_ov123_02299650(param, 32) != 0) {
        func_ov123_02299630(param, 32);
        func_0200277c(3);
    }
}
