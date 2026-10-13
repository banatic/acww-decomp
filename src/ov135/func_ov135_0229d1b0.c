/* func_ov135_0229d1b0 @ 0x0229d1b0, 0x28 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int a, int b);
extern void func_ov002_022080a0(int a, int b);
extern void func_ov135_0229ca1c(int a);
extern int func_ov135_0229d128(int a);

int func_ov135_0229d1b0(int a)
{
    if (func_ov002_02207f48(a, 0)) {
        func_ov002_022080a0(a, 2);
        func_ov135_0229ca1c(a);
    }
    return func_ov135_0229d128(a);
}
