/* func_ov096_022a0d60 @ 0x022a0d60, 0x48 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov096_0229c4ec(int);
extern int func_ov002_02208054(int, int);
extern int func_ov002_02208098(int, int);
extern int MATH_CalcMD5(int);
extern void func_ov096_0229c514(int);

void func_ov096_022a0d60(int r0)
{
    int r4 = r0;
    if (func_0206f56c()) {
        func_ov096_0229c4ec(r4);
    } else {
        if (func_ov002_02208054(r4, 1)) {
            func_ov002_02208098(r4, 0x17);
        } else {
            if (MATH_CalcMD5(r4 + 0x2d9c)) {
                func_ov096_0229c514(r4);
            }
        }
    }
}
