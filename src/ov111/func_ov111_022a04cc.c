/* func_ov111_022a04cc @ 0x022a04cc, 0x64 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov095_0229cce0(void *p);
extern void func_ov111_0229f0cc(void *p);
extern int func_ov095_0229bf0c(void *p);
extern void *func_ov095_0229c548(void *p);
extern void *func_ov095_0229c448(void *p, void *x, int n);
extern void func_ov111_0229f730(void *p, void *x);
extern void func_ov095_0229c8e4(void *p, void *x);

void func_ov111_022a04cc(void *self)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov095_0229cce0((char *) self + 0xac);
        func_ov111_0229f0cc(self);
    } else if (func_ov095_0229bf0c((char *) self + 0xac) != 0) {
        void *x = func_ov095_0229c548((char *) self + 0xac);
        func_ov111_0229f730(self, func_ov095_0229c448((char *) self + 0xac, x, 9));
        func_ov095_0229c8e4((char *) self + 0xac, x);
    }
}
