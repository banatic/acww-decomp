/* func_ov126_022a0ec4 @ 0x022a0ec4, 0x5c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *self, int a);
extern int func_ov002_02208008(void *self);
extern int func_ov126_022a0768(void *self, int v);
extern void func_ov095_0229b3ec(void *p);
extern void func_ov126_022a0680(void *self);
extern void func_ov126_022a08c4(void *self);
extern void func_ov126_022a0168(void *self);
extern void func_ov126_0229ff0c(void *self);
extern void RtcSendPxiCommand(int cmd);

void func_ov126_022a0ec4(void *self)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov002_02208098(self, 6);
    } else {
        int ret = func_ov002_02208008(self);
        if (func_ov126_022a0768(self, ret) == 1) {
            func_ov095_0229b3ec((unsigned char *) self + 0x19c);
            func_ov126_022a0680(self);
            func_ov126_022a08c4(self);
            func_ov126_022a0168(self);
            func_ov126_0229ff0c(self);
            RtcSendPxiCommand(0x15);
        }
    }
}
