/* func_ov099_0229d718 @ 0x0229d718, 0x8c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8; // 0x021fbdd8
extern unsigned char data_021fbddc; // 0x021fbddc
extern unsigned char data_021f6c58; // 0x021f6c58
extern unsigned char data_021f6c54; // 0x021f6c54

extern int func_ov002_02208054(void *self, int arg);
extern void func_ov099_0229c470(void *self);
extern int func_ov002_02208b00(void *ptr, int a, int b);
extern void func_ov002_02209114(void *ptr, int a, int b);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);

void func_ov099_0229d718(unsigned char *self)
{
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov099_0229c470(self);
    } else {
        unsigned int cond = (data_021fbdd8 != 0 && data_021fbddc != 0);
        if (cond > 0) {
            int ret = func_ov002_02208b00(self + 0x22d8, data_021f6c58, data_021f6c54);
            if (ret >= 0) {
                func_ov002_02209114(self + 0x22d8, ret, 1);
                *(self + 0x290b) = *(self + ret + 0x26c5);
                func_ov002_02208098(self, 0x12);
            }
        }
    }
}
