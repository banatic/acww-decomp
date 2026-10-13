/* func_ov135_0229d148 @ 0x0229d148, 0x30 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int, int);
extern void func_020027f0(int);
extern void func_ov002_022080a0(int, int);
extern void func_ov135_0229d128(int);

void func_ov135_0229d148(int param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0(param, 5);
    } else {
        func_ov135_0229d128(param);
    }
}
