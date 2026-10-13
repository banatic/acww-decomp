/* func_ov122_022a116c @ 0x022a116c, 0xb4 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(unsigned char *self);
extern void func_ov122_0229efd8(unsigned char *self, int param);
extern void func_ov122_0229f0a8(unsigned char *self);
extern int func_ov002_02208054(unsigned char *self, int param);
extern void func_ov122_0229ff2c(unsigned char *self);
extern int func_ov002_02208aec(unsigned char *base, unsigned char a, unsigned char b);
extern void func_ov002_022090b0(unsigned char *base, int param);
extern int func_ov002_02208a8c(unsigned char *base, unsigned char a, unsigned char b);
extern void func_ov002_02208098(unsigned char *self, int param);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov122_022a116c(unsigned char *self)
{
    unsigned int flag;
    int ret;

    if (func_0206f56c(self)) {
        func_ov122_0229efd8(self, 0x2000);
        func_ov122_0229f0a8(self);
        return;
    }

    if (func_ov002_02208054(self, 1)) {
        func_ov122_0229ff2c(self);
        return;
    }

    if (data_021fbdd8 && data_021fbddc) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag > 0) {
        ret = func_ov002_02208aec(self + 0x42b0, data_021f6c58, data_021f6c54);
        if (ret >= 0) {
            func_ov002_022090b0(self + 0x42b0, ret);
            self[0xb6] = (unsigned char) func_ov002_02208a8c(self + 0x42b0, self[0xb7], (unsigned char) ret);
            func_ov002_02208098(self, 0x17);
        } else {
            func_ov122_0229f0a8(self);
        }
    }
}
