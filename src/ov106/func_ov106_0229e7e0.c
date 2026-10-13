/* func_ov106_0229e7e0 @ 0x0229e7e0, 0x80 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int flag);
extern void func_ov106_0229d75c(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov106_0229d2e4(char *a, int b, int c, int d);
extern void func_ov106_0229d60c(void *p, int val);
extern int func_ov002_0220a784(void *ptr, int x);
extern int func_ov106_0229c378(void *arg);

void func_ov106_0229e7e0(void *self)
{
    int result;
    int cond;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov106_0229d75c(self);
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
    result = func_ov106_0229d2e4((char *) self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (result != 0x20) {
        func_ov106_0229d60c(self, result);
        return;
    }
    if (func_ov002_0220a784((char *) self + 0x3fb4, 9) != 0) {
        func_ov106_0229c378(self);
    }
}
