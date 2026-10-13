/* func_ov126_022a0ae0 @ 0x022a0ae0, 0xb0 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a720(void *self, int arg);
extern void func_ov126_0229f7b8(void *self, int arg);
extern void func_ov126_0229f7a8(void *self, int arg);
extern int func_ov126_0229f7c8(void *self, int arg);
extern void RtcSendPxiCommand(int cmd);
extern int func_0206fca4(void);
extern void func_ov002_02208098(void *self, int arg);

void func_ov126_022a0ae0(void *self, int flag)
{
    if (flag == 0) {
        func_ov002_0220a720((char *) self + 0x3dc4, 6);
        if (*(unsigned char *) ((char *) self + 0xad) == 1) {
            func_ov126_0229f7b8(self, 0x40);
        } else {
            func_ov126_0229f7a8(self, 0x40);
        }
    } else {
        func_ov002_0220a720((char *) self + 0x3dc4, 7);
        func_ov126_0229f7b8(self, 0x40);
    }
    if (func_ov126_0229f7c8(self, 0x20) != 0) {
        if (func_ov126_0229f7c8(self, 0x40) != 0) {
            RtcSendPxiCommand(0x2a);
        } else {
            if (func_0206fca4() == 0x19) {
                RtcSendPxiCommand(0x27);
            } else {
                RtcSendPxiCommand(0x29);
            }
        }
    } else {
        if (func_ov126_0229f7c8(self, 0x40) != 0) {
            RtcSendPxiCommand(0x28);
        } else {
            RtcSendPxiCommand(0x27);
        }
    }
    *(unsigned char *) ((char *) self + 0x8c) = 3;
    func_ov002_02208098(self, 0xf);
}
