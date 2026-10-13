/* func_ov103_0229d82c @ 0x0229d82c, 0x64 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int flag);
extern void func_ov103_0229cfc0(void *self);
extern int func_ov103_0229cd98(void *self, unsigned char a, unsigned char b, int c);
extern void func_ov103_0229cf18(void *self, int result);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov103_0229d82c(void *self)
{
    unsigned int flag;
    int result;

    if (func_ov002_02208054(self, 1)) {
        func_ov103_0229cfc0(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (flag > 0) {
        result = func_ov103_0229cd98(self, data_021f6c58, data_021f6c54, 1);
        if (result != 0x15) {
            func_ov103_0229cf18(self, result);
        }
    }
}
