/* func_ov096_022a0170 @ 0x022a0170, 0x1a bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_022a018c(void);
extern void func_ov002_02208098(int, int);

void func_ov096_022a0170(int param)
{
    int r4 = param;
    if (func_ov096_022a018c() != 0) {
        func_ov002_02208098(r4, 0x1f);
    }
}
