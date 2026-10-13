/* func_ov125_022a02b4 @ 0x022a02b4, 0x80 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(unsigned char *self, int a);
extern void func_ov125_0229feb8(unsigned char *self);
extern int func_ov125_0229fdc4(unsigned char *self);
extern void func_ov002_0220a720(unsigned char *p, int a);
extern void func_ov002_02208098(unsigned char *p, int a);
extern void func_ov125_0229fc90(unsigned char *self);
extern void func_ov125_0229fc24(unsigned char *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

void func_ov125_022a02b4(unsigned char *self)
{
    unsigned int flag;
    int n;

    if (func_ov002_02208054(self, 1)) {
        func_ov125_0229feb8(self);
        return;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag > 0) {
        n = func_ov125_0229fdc4(self);
        if (n == 8) {
            func_ov002_0220a720(self + 0x6a8, 9);
            func_ov002_02208098(self, 10);
        } else if (n != 9) {
            func_ov125_0229fc90(self);
            self[0x87b] = (unsigned char) n;
            func_ov125_0229fc24(self);
        }
    }
}
