/* func_ov102_0229e560 @ 0x0229e560, 0x58 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern void func_ov102_0229cb50(void *self);
extern int func_ov002_02207d24(void *self, int flag);
extern void func_ov102_0229c460(void *self, int flag);
extern void func_ov102_0229e0ec(void *self);
extern void func_ov102_0229e5b8(void *self);
extern void func_ov102_0229e0e4(void *self);

int func_ov102_0229e560(unsigned char *self)
{
    unsigned char *p;
    int v;

    func_0206f58c();
    if (func_0206f56c() == 0) {
        goto label_229e59a;
    }
    p = self + 0x8d;
    v = *p;
    if (v == 0 || v == 1 || v == 3) {
        func_ov102_0229cb50(self);
        func_ov002_02207d24(self + 0x218c, 0);
        func_ov102_0229c460(self, 0);
    }
label_229e59a:
    func_ov102_0229e0ec(self);
    func_ov102_0229e5b8(self);
    func_ov102_0229e0e4(self);
    return 1;
}
