/* func_ov142_0229b2f8 @ 0x0229b2f8, 0x58 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int cmd);
extern void func_ov002_0220a720(void *self, int arg);
extern void func_ov002_02207e9c(void *self, int arg1, int arg2);
extern void func_ov002_02208098(void *self, int arg);
extern void func_ov142_02299658(void *self, int arg);
extern void func_ov142_02299938(void *self);

void func_ov142_0229b2f8(void *self)
{
    RtcSendPxiCommand(0x2a);
    func_ov002_0220a720((char *) self + 0x194, 4);
    *((unsigned char *) self + 0x8c) = 6;
    func_ov002_02207e9c(self, 0, 0);
    func_ov002_02208098(self, 0xd);
    func_ov142_02299658(self, 0x80);
    *((unsigned char *) self + 0xc0) = 0x12;
    *((unsigned char *) self + 0xbf) = 5;
    func_ov142_02299938(self);
}
