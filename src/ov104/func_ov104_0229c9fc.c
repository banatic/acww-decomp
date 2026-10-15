/* func_ov104_0229c9fc @ 0x0229c9fc, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_ov104_0229c354(int, int);
extern void func_ov104_0229c344(int, int);
extern void *func_ov002_0220a720(int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov104_0229c9fc(int param)
{
    RtcSendPxiCommand(0x28);
    func_ov104_0229c354(param, 0x400);
    func_ov002_0220a720(param + 0x41b4, 7);
    func_ov002_02208098((void *) (param), 0x1b);
    *(char *) (param + 0x8c) = 4;
    func_ov104_0229c344(param, 0x100);
}
