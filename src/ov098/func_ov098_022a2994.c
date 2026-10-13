/* func_ov098_022a2994 @ 0x022a2994, 0x1c bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229cbbc(void);
extern int func_ov003_0222c364(void);
extern void func_ov096_0229fb9c(int);

void func_ov098_022a2994(int param)
{
    int result;

    func_ov096_0229cbbc();
    result = func_ov003_0222c364();
    if (result == 0) {
        func_ov096_0229fb9c(param);
    }
}
