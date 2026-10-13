/* func_ov112_022a0e24 @ 0x022a0e24, 0x6c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_02208054(char *p, int n);
extern int func_ov002_0220a784(char *p, int n);
extern void func_ov112_0229fe84(char *p);
extern void func_ov112_0229ffdc(char *p);
extern void func_ov112_0229ffa0(char *p);

void func_ov112_022a0e24(char *self)
{
    unsigned int flag;

    if (func_ov002_02208054(self, 1)) {
        func_ov112_0229fe84(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc);
    if (flag > 0) {
        if (func_ov002_0220a784(self + 0x427c, 3)) {
            func_ov112_0229ffdc(self);
            return;
        }
        if (func_ov002_0220a784(self + 0x427c, 4)) {
            func_ov112_0229ffa0(self);
        }
    }
}
