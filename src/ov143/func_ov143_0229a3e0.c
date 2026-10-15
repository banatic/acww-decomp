/* func_ov143_0229a3e0 @ 0x0229a3e0, 0x24 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov143_02299a9c(int parameter0);
extern void RtcSendPxiCommand(int);
extern void *func_ov002_0220a720(void *ptr, int);

void func_ov143_0229a3e0(void *arg)
{
    func_ov143_02299a9c((int) (arg));
    RtcSendPxiCommand(0x2a);
    func_ov002_0220a720((char *) arg + 0x110, 4);
}
