/* func_ov126_022a1e8c @ 0x022a1e8c, 0x44 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0206fca4(void);
extern void *func_020ee45c(void *a);
extern int func_ov090_0229936c(void *x);
extern void func_ov090_022990d0(void *x);
extern void func_ov092_0229929c(void *x);
extern void func_ov126_022a149c(void *a);

int func_ov126_022a1e8c(void *a)
{
    unsigned int res = func_0206fca4();
    if (res >= 24 && res <= 27) {
        void *x = func_020ee45c(a);
        if (func_ov090_0229936c(x) == 6) {
            func_ov090_022990d0(x);
        }
    } else {
        func_ov092_0229929c(func_020ee45c(a));
    }
    func_ov126_022a149c(a);
    return 1;
}
