/* func_ov104_0229ed1c @ 0x0229ed1c, 0x50 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int a);
extern void func_ov104_0229c344(int a, int b);
extern void func_ov002_02207f04(int a, int b, int c, int d, int e);
extern void func_ov002_02208090(int a, int b);
extern void func_ov104_0229ecc0(int a);
extern void func_ov104_0229eb48(int a);

void func_ov104_0229ed1c(int arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(4);
        func_ov104_0229c344(arg, 0x200);
        func_ov002_02207f04(arg, 8, 0, 0, 0x30);
        func_ov002_02208090(arg, 6);
        func_ov104_0229ecc0(arg);
    } else {
        func_ov104_0229eb48(arg);
    }
}
