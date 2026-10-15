/* func_ov112_0229ffa0 @ 0x0229ffa0, 0x3c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov112_0229fe70(void *arg, int size);
extern void func_ov112_0229f45c(void *object, unsigned char flags, int mode);
extern void func_ov112_0229fe50(void *arg, int size);
extern void RtcSendPxiCommand(int cmd);

void func_ov112_0229ffa0(void *arg)
{
    if (func_ov112_0229fe70(arg, 0x2000) != 0) {
        RtcSendPxiCommand(0x29);
    } else {
        RtcSendPxiCommand(0x2a);
    }

    func_ov112_0229f45c(arg, 6, 4);
    func_ov112_0229fe50(arg, 0x400);
}
