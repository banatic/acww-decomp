/* func_ov098_022a29b0 @ 0x022a29b0, 0x1e bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229cbbc(void);
extern int func_ov003_0222c364(void);
extern void func_ov002_02208098(int, int);

void func_ov098_022a29b0(int param)
{
    int result;

    func_ov096_0229cbbc();
    result = func_ov003_0222c364();
    if (result == 1) {
        func_ov002_02208098(param, 0x34);
    }
}
