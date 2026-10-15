/* func_ov112_022a0c10 @ 0x022a0c10, 0x5c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;

extern void func_ov112_0229f270(void *self);
extern int func_ov095_0229bf0c(void *self);
extern int func_ov095_0229c548(void *self);
extern int func_ov095_0229c448(void *self, int a, int b);
extern int func_ov112_022a03ac(void *self, int a);
extern void func_ov095_0229c8e4(void *self, int a);

void func_ov112_022a0c10(void *self)
{
    int r;

    if (!(data_021fbe40 & 1)) {
        func_ov112_0229f270(self);
        return;
    }
    if (func_ov095_0229bf0c((char *) self + 0x384) == 0) {
        return;
    }
    r = func_ov095_0229c548((char *) self + 0x384);
    func_ov112_022a03ac(self, func_ov095_0229c448((char *) self + 0x384, r, 9));
    func_ov095_0229c8e4((char *) self + 0x384, r);
}
