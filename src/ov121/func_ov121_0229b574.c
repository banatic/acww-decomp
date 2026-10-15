/* func_ov121_0229b574 @ 0x0229b574, 0xd8 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern int func_ov002_02208054(unsigned char *, int);
extern int func_ov002_02208b00(unsigned char *, unsigned char, unsigned char);
extern unsigned char func_ov121_0229ab80(unsigned char *, int);
extern void func_ov121_0229a53c(unsigned char *);
extern void func_ov121_0229a1e4(unsigned char *);
extern unsigned char *func_ov002_02208098(unsigned char *, unsigned char value);
extern void func_ov002_02209114(unsigned char *, int, int);
extern void RtcSendPxiCommand(int);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov121_0229b574(unsigned char *self)
{
    int ret, flag;
    unsigned char byte;

    if (func_0206f56c() != 0) {
        func_ov121_0229a53c(self);
        return;
    }

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov121_0229a1e4(self);
        func_ov002_02208098(self, 0xc);
        self[0xb1] = self[0xaf];
        return;
    }

    {
        unsigned int cond = 0;
        if (data_021fbdd8 != 0 && data_021fbddc != 0) {
            cond = 1;
        }
        if (cond > 0) {
            ret = func_ov002_02208b00(self + 0x528, data_021f6c58, data_021f6c54);
            if (ret < 0) {
                return;
            }

            flag = 1;
            self[0xb2] = func_ov121_0229ab80(self, ret);
            byte = self[0xb2];

            switch (byte) {
                case 0:
                case 1:
                case 2:
                case 3:
                    RtcSendPxiCommand(0x50);
                    break;
                case 4:
                case 5:
                    break;
                case 6:
                    flag = 0;
                    break;
            }

            func_ov002_02209114(self + 0x528, ret, flag);
            func_ov002_02208098(self, 0xf);
        }
    }
}
