/* func_ov098_022a29b0 @ 0x022a29b0, 0x1e bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov096_0229cbbc(void *self);
extern int func_ov003_0222c364(int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov098_022a29b0(int param)
{
    int result;

    result = func_ov003_0222c364((int) func_ov096_0229cbbc((void *) param));
    if (result == 1) {
        func_ov002_02208098(param, 0x34);
    }
}
