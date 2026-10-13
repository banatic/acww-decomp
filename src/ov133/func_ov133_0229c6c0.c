/* func_ov133_0229c6c0 @ 0x0229c6c0, 0x2a bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee45c(void *self);
extern int func_ov090_0229936c(void *x);
extern void func_ov090_022990d0(void *x);
extern void func_ov133_0229c1dc(void *self);

int func_ov133_0229c6c0(void *self)
{
    void *x = func_020ee45c(self);

    if (func_ov090_0229936c(x) == 6) {
        func_ov090_022990d0(x);
    }
    func_ov133_0229c1dc(self);
    return 1;
}
