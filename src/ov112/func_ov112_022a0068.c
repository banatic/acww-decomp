/* func_ov112_022a0068 @ 0x022a0068, 0x44 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int cmd);
extern void func_ov112_0229fe50(int a, int b);
extern void func_ov112_0229f45c(int a, int b, int c);
extern void func_ov112_0229fe60(int a, int b);
extern void func_ov112_0229f1f4(int a);
extern void func_ov112_0229f8e4(int a);
extern void func_ov112_0229fd20(int a);

void func_ov112_022a0068(int param)
{
    RtcSendPxiCommand(0x29);
    func_ov112_0229fe50(param, 0x2000);
    func_ov112_0229f45c(param, 2, 9);
    func_ov112_0229fe60(param, 0x400);
    func_ov112_0229f1f4(param);
    func_ov112_0229f8e4(param);
    func_ov112_0229fd20(param);
}
