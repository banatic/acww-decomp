/* func_ov126_022a1228 @ 0x022a1228, 0xac bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *p, int x);
extern void func_ov126_022a0c00(void *p);
extern int func_ov095_0229bf48(void *p);
extern int func_ov126_022a00a4(void *p);
extern int func_ov126_022a07e8(void *p);
extern int func_ov095_0229aff0(void *p);
extern void func_ov095_0229c22c(void *p, int a, int b, int c);
extern void func_ov126_022a0168(void *p);
extern int func_ov126_022a04e8(void *p);
extern void func_ov002_02208098(void *p, int x);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;

void func_ov126_022a1228(void *self)
{
    int r4;
    unsigned int ok;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov126_022a0c00(self);
        return;
    }
    r4 = func_ov095_0229bf48((char *) self + 0x19c);
    ok = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (ok > 0) {
        if (func_ov126_022a00a4(self) != 0) {
            return;
        }
        if (func_ov126_022a07e8(self) != 0) {
            return;
        }
        if (func_ov095_0229aff0((char *) self + 0x19c) != 0) {
            func_ov095_0229c22c((char *) self + 0x19c, 9, 6, 1);
            func_ov126_022a0168(self);
            return;
        } else {
            int t;
            if (data_021f6c54 < 0x48) {
                return;
            }
            if (r4 != 0) {
                return;
            }
            t = func_ov126_022a04e8(self);
            if (t == 0) {
                return;
            }
            if (t != 1) {
                return;
            }
            func_ov002_02208098(self, 2);
        }
    }
}
