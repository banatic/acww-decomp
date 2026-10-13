/* func_ov107_0229daa4 @ 0x0229daa4, 0x80 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int flag);
extern void func_ov107_0229d4a0(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov107_0229d31c(int a, int b, int c, int d);
extern void func_ov107_0229d3f8(void *p, int val);
extern int func_ov002_0220a784(void *ptr, int x);
extern void func_ov107_0229cb14(void *param);

void func_ov107_0229daa4(void *self)
{
    int result;
    int cond;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov107_0229d4a0(self);
        return;
    }
    if (data_021fbdd8 == 0) {
        goto isfalse;
    }
    if (data_021fbddc == 0) {
        goto isfalse;
    }
    cond = 1;
    goto done;
isfalse:
    cond = 0;
done:
    if (cond == 0) {
        return;
    }
    result = func_ov107_0229d31c((int) self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (result != 0x10) {
        func_ov107_0229d3f8(self, result);
        return;
    }
    if (func_ov002_0220a784((char *) self + 0x2828, 9) != 0) {
        func_ov107_0229cb14(self);
    }
}
