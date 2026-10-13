/* func_ov123_02299980 @ 0x02299980, 0x2e bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_02299650(int a, int b);
extern void func_ov123_02299930(int a);
extern void func_ov123_02299954(int a);
extern void RtcSendPxiCommand(int cmd);

void func_ov123_02299980(int a)
{
    if (func_ov123_02299650(a, 0x20) != 0) {
        func_ov123_02299930(a);
        RtcSendPxiCommand(0x42);
    } else {
        func_ov123_02299954(a);
        RtcSendPxiCommand(0x41);
    }
}
