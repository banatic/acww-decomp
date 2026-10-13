/* func_ov123_0229bd9c @ 0x0229bd9c, 0x60 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

extern int func_ov002_02208054(unsigned char *self, int param);
extern void func_ov123_0229b67c(unsigned char *self);
extern int func_ov123_0229afa8(unsigned char *self);
extern void func_ov123_0229a4bc(unsigned char *self);
extern void func_ov123_0229ae84(unsigned char *self);

void func_ov123_0229bd9c(unsigned char *self)
{
    unsigned int flag;
    int res;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov123_0229b67c(self);
    } else {
        flag = (data_021fbdd8 && data_021fbddc);
        if (flag > 0) {
            res = func_ov123_0229afa8(self);
            if (res == 0x21) {
                func_ov123_0229a4bc(self);
            } else if (res != 0x22) {
                self[0xa5] = (unsigned char) res;
                func_ov123_0229ae84(self);
            }
        }
    }
}
