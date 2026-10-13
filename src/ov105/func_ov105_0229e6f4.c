/* func_ov105_0229e6f4 @ 0x0229e6f4, 0x34 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(char *p, int n);
extern void func_ov002_02208098(char *p, int n);
extern int MATH_CalcMD5(char *p);
extern void func_ov105_0229c710(char *p);

void func_ov105_0229e6f4(char *param0)
{
    if (func_ov002_02208054(param0, 1) != 0) {
        func_ov002_02208098(param0, 9);
    } else {
        if (MATH_CalcMD5(param0 + 0x2d40) != 0) {
            func_ov105_0229c710(param0);
        }
    }
}
