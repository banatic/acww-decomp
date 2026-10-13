/* func_ov144_02299ac4 @ 0x02299ac4, 0x84 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov144_0229a798(void *self);
extern int func_ov144_0229a71c(void *self);
extern int func_ov144_0229a5f4(void *self);
extern int func_ov144_0229a5bc(void *self);
extern int func_ov144_02299b48(void *self, unsigned int x);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void *p);
extern void func_ov002_02208098(void *self, int a);
extern void RtcSendPxiCommand(unsigned int cmd);

int func_ov144_02299ac4(unsigned char *self, unsigned int cmd)
{
    if (cmd <= 8) {
        short k = *(short *) (self + 0xb6);
        if (func_ov144_02299b48(self, cmd + k)) {
            RtcSendPxiCommand(0x29);
        }
        return 0;
    } else {
        switch (cmd - 9) {
            case 0:
                func_ov144_0229a798(self);
                return 1;
            case 2:
                return func_ov144_0229a71c(self);
            case 3:
                return func_ov144_0229a5f4(self);
            case 4:
                func_ov144_0229a5bc(self);
                return 1;
            case 1:
                func_ov002_0220a574(self + 0x128);
                func_ov002_0220a4bc(self + 0x128);
                func_ov002_02208098(self, 4);
                return 1;
        }
        return 0;
    }
}
