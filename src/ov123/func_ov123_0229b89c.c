/* func_ov123_0229b89c @ 0x0229b89c, 0x50 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_02299630(void *, int);
extern void func_ov123_0229b65c(void *);
extern void RtcSendPxiCommand(int command);
extern int func_ov002_02208008(void *);
extern int func_ov123_022999b0(void *, int, int);
extern void func_ov123_0229a340(void *);

extern volatile unsigned short data_021fbe40;

void func_ov123_0229b89c(void *arg)
{
    if ((data_021fbe40 & 2) == 0) {
        func_ov123_02299630(arg, 0x800);
        func_ov123_0229b65c(arg);
        RtcSendPxiCommand(0x86d);
    } else {
        int ret = func_ov002_02208008(arg);
        if (func_ov123_022999b0(arg, ret, 0) != 0) {
            func_ov123_0229a340(arg);
        }
    }
}
