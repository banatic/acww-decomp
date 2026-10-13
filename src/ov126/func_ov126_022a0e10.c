/* func_ov126_022a0e10 @ 0x022a0e10, 0x88 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(const void *);
extern const void *func_ov095_02299a00(const void *);
extern const void *func_ov095_0229c448(const void *, const void *, int);
extern int func_ov126_022a03dc(const void *, const void *);
extern void func_ov095_0229bf3c(const void *);
extern void func_ov002_02208098(const void *, int);
extern void func_ov095_0229c8e4(const void *, const void *);
extern void func_ov095_0229cce0(const void *);
extern void func_ov126_0229fec0(const void *);

extern unsigned short data_021fbe40;

void func_ov126_022a0e10(const void *self)
{
    if (func_0208e484((const char *) self + 0x3f90) != 0) {
        const void *r4 = func_ov095_02299a00((const char *) self + 0x19c);
        const void *tmp = func_ov095_0229c448((const char *) self + 0x19c, r4, 9);
        int ret = func_ov126_022a03dc(self, tmp);
        if (ret == 1 && ((data_021fbe40 & 1) != 0)) {
            func_ov095_0229bf3c((const char *) self + 0x19c);
            func_ov002_02208098(self, 0xa);
            func_ov095_0229c8e4((const char *) self + 0x19c, r4);
            return;
        }
        if (ret == 4) {
            func_ov095_0229cce0((const char *) self + 0x19c);
            return;
        } else if (ret == 3) {
            return;
        } else {
            func_ov126_0229fec0(self);
        }
    }
}
