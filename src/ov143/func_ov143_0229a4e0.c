/* func_ov143_0229a4e0 @ 0x0229a4e0, 0x6c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int kind);
extern void func_ov143_0229a2a4(void *self);
extern int func_ov002_0220a784(void *field, int kind);
extern void func_ov143_0229a404(void *self);
extern void func_ov143_0229a3e0(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

void func_ov143_0229a4e0(void *self)
{
    unsigned int flag;

    if (func_ov002_02208054(self, 1)) {
        func_ov143_0229a2a4(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (flag == 0) {
        return;
    }

    if (func_ov002_0220a784((char *) self + 0x110, 3)) {
        func_ov143_0229a404(self);
    } else if (func_ov002_0220a784((char *) self + 0x110, 4)) {
        func_ov143_0229a3e0(self);
    }
}
