/* func_ov112_022a0028 @ 0x022a0028, 0x40 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_ov112_0229fe60(int, int);
extern void func_ov112_0229f45c(int, int, int);
extern void func_ov112_0229f8e4(int);
extern void func_ov112_0229fd20(int);

void func_ov112_022a0028(int param)
{
    RtcSendPxiCommand(0x2a);
    func_ov112_0229fe60(param, 0x2000);
    func_ov112_0229f45c(param, 2, 8);
    func_ov112_0229fe60(param, 0x400);
    func_ov112_0229f8e4(param);
    func_ov112_0229fd20(param);
}
