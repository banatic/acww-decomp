/* func_ov112_022a0e90 @ 0x022a0e90, 0x5c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov095_0229bf0c(void *p);
extern int func_ov095_0229c548(void *p);
extern void *func_ov095_0229c448(void *p, int x, int n);
extern void func_ov095_0229c8e4(void *p, int x);
extern int func_ov112_022a03ac(void *self, void *ret);

void func_ov112_022a0e90(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 0);
        return;
    }
    if (func_ov095_0229bf0c((char *) self + 0x384) != 0) {
        int x = func_ov095_0229c548((char *) self + 0x384);
        void *ret = func_ov095_0229c448((char *) self + 0x384, x, 9);
        func_ov112_022a03ac(self, ret);
        func_ov095_0229c8e4((char *) self + 0x384, x);
    }
}
