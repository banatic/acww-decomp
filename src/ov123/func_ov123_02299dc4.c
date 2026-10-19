/* func_ov123_02299dc4 @ 0x02299dc4, 0x64 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_02299650(void *p, int n);
extern void func_ov123_02299630(void *p, int n);
extern void func_ov123_02299640(void *p, int n);
extern void func_0200467c(int cmd);

void func_ov123_02299dc4(void *arg)
{
    if (func_ov123_02299650(arg, 0x80)) {
        func_ov123_02299630(arg, 0x80);
    } else {
        func_ov123_02299640(arg, 0x80);
    }

    if (func_ov123_02299650(arg, 0x4000)) {
        func_0200467c(0x86c);
        func_ov123_02299630(arg, 0x4000);
    } else {
        func_0200467c(0x86b);
        func_ov123_02299640(arg, 0x4000);
    }

    func_ov123_02299640(arg, 0x40);
}
