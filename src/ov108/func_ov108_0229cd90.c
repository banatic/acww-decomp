/* func_ov108_0229cd90 @ 0x0229cd90, 0x28 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a720(void *p, int n);
extern void func_ov002_02208098(void *p, int n);
extern int RtcSendPxiCommand(int cmd);

int func_ov108_0229cd90(void *arg)
{
    func_ov002_0220a720((char *) arg + 0x2a0c, 9);
    func_ov002_02208098(arg, 23);
    return RtcSendPxiCommand(40);
}
