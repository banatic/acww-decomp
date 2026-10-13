/* func_ov112_0229ffdc @ 0x0229ffdc, 0x4c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov112_0229f45c(void *this, int a, int b);
extern int func_ov112_0229fe70(void *this, int n);
extern void RtcSendPxiCommand(int cmd);
extern void func_02077ed4(void *ptr);
extern void func_ov112_0229efe8(void *this);
extern void func_020984e8(void);
extern void func_02099640(void);
extern void func_0209a8c4(void);

void func_ov112_0229ffdc(void *this)
{
    func_ov112_0229f45c(this, 10, 3);
    if (func_ov112_0229fe70(this, 0x2000) != 0) {
        RtcSendPxiCommand(0x28);
    } else {
        func_02077ed4((char *) this + 0xC4);
        RtcSendPxiCommand(0x27);
        func_ov112_0229efe8(this);
        func_020984e8();
        func_02099640();
        func_0209a8c4();
    }
}
