/* func_ov140_0229add0 @ 0x0229add0, 0x28 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int a, int b);
extern void func_ov002_022080a0(int a, int b);
extern void func_ov140_0229a7ac(int a);
extern void func_ov140_0229ad4c(int a);

void func_ov140_0229add0(int param)
{
    if (func_ov002_02207f48(param, 0) != 0) {
        func_ov002_022080a0(param, 2);
        func_ov140_0229a7ac(param);
    }
    func_ov140_0229ad4c(param);
}
