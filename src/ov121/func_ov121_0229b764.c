/* func_ov121_0229b764 @ 0x0229b764, 0x70 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int a);
extern unsigned char *func_ov121_0229afd8(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov121_0229ae18(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov002_02207cf8(void *p);
extern void RtcSendPxiCommand(int cmd);

void func_ov121_0229b764(void *self)
{
    unsigned int cond;
    int r;

    if (func_ov002_02208054(self, 1)) {
        func_ov121_0229afd8(self);
        return;
    }
    if (data_021fbdd8 == 0) {
        goto zero;
    }
    if (data_021fbddc == 0) {
        goto zero;
    }
    cond = 1;
    goto done;
zero:
    cond = 0;
done:
    if (cond) {
        r = func_ov121_0229ae18(self);
        if (r == 0x18) {
            return;
        }
        func_ov002_02208098(self, 1);
        *((unsigned char *) self + 0xad) = r;
        func_ov002_02207cf8((unsigned char *) self + 0x2d8);
        RtcSendPxiCommand(0xc);
    }
}
