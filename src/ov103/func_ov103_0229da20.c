/* func_ov103_0229da20 @ 0x0229da20, 0x48 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

void func_ov103_0229da20(int arg0)
{
    extern void func_020027f0(int);
    extern void func_ov103_0229c2d4(int, int);
    extern void func_ov103_0229dd10(int);
    extern int func_ov002_02207f3c(int, int);
    extern void func_ov002_02207e80(int, int, int, int);

    if (func_ov002_02207f3c(arg0, 0) != 0) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov103_0229c2d4(arg0, 0x80);
        func_ov103_0229dd10(arg0);
    } else {
        func_ov002_02207e80(arg0, 3, 0, 0);
        func_ov002_02207e80(arg0, 4, 0, 0);
    }
}
