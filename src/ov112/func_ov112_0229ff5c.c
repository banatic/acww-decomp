/* func_ov112_0229ff5c @ 0x0229ff5c, 0x44 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_ov112_0229fe50(int, int);
extern void func_ov112_0229f3e0(int);
extern void func_ov112_0229fb7c(int, int);
extern void func_ov112_0229fe60(int, int);
extern void func_ov002_022080a0(int, int);
extern void func_ov002_02208090(int, int);

void func_ov112_0229ff5c(int param)
{
    RtcSendPxiCommand(0x28);
    func_ov112_0229fe50(param, 0x40);
    func_ov112_0229f3e0(param);
    func_ov112_0229fb7c(param, 0);
    func_ov002_02208090(param, 0xc);
    func_ov002_022080a0(param, 1);
    func_ov112_0229fe60(param, 0x2000);
}
