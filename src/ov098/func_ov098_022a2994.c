/* func_ov098_022a2994 @ 0x022a2994, 0x1c bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov096_0229cbbc(void *self);
extern int func_ov003_0222c364(int);
extern void func_ov096_0229fb9c(int);

void func_ov098_022a2994(int param)
{
    int result;

    result = func_ov003_0222c364((int) func_ov096_0229cbbc((void *) param));
    if (result == 0) {
        func_ov096_0229fb9c(param);
    }
}
