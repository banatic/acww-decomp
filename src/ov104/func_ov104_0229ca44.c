/* func_ov104_0229ca44 @ 0x0229ca44, 0x5c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(unsigned int cmd);
extern void func_ov104_0229c344(void *self, unsigned int value);
extern void *func_ov002_0220a720(void *ptr, int value);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_02073d90(void *ptr);
extern void func_ov104_0229c558(void *self);
extern void *data_020ccf94;

void func_ov104_0229ca44(unsigned char *self)
{
    RtcSendPxiCommand(0x27);
    func_ov104_0229c344(self, 0x400);
    func_ov002_0220a720(self + 0x41b4, 9);
    func_ov002_02208098((void *) (self), 0x1b);
    self[0x8c] = 4;
    func_ov104_0229c344(self, 0x100);
    if (func_02073d90(data_020ccf94) != 0) {
        func_ov104_0229c558(self);
    }
}
