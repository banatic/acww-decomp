/* func_ov099_0229d814 @ 0x0229d814, 0x80 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int flag);
extern void func_ov099_0229d110(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov099_0229ceb8(char *a, int b, int c, int d);
extern int func_ov099_0229cdc4(char *a, int b, int c, int d);
extern void func_ov099_0229d050(void *p, int val);

void func_ov099_0229d814(void *self)
{
    int result;
    int cond;
    unsigned char a;
    unsigned char b;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov099_0229d110(self);
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
    a = data_021f6c58;
    b = data_021f6c54;
    result = func_ov099_0229ceb8((char *) self, a, b, 1);
    if (result != 0x1d) {
        func_ov099_0229d050(self, result);
        return;
    }
    result = func_ov099_0229cdc4((char *) self, a, b, 1);
    if (result != 0x1d) {
        func_ov099_0229d050(self, result);
    }
}
