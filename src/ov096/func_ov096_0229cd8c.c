/* func_ov096_0229cd8c @ 0x0229cd8c, 0x60 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229e4a4(int param1, int param2);
extern void func_ov002_02208d4c(int param1, int param2, int param3);

void func_ov096_0229cd8c(int param1)
{
    if (func_ov096_0229e4a4(param1, 5) != 0xfff1) {
        func_ov002_02208d4c(param1 + 0x294c, 0x75, 0x11);
    }
    if (func_ov096_0229e4a4(param1, 4) != 0xfff1) {
        func_ov002_02208d4c(param1 + 0x294c, 0x76, 0x10);
    }
    if (func_ov096_0229e4a4(param1, 3) != 0xfff1) {
        func_ov002_02208d4c(param1 + 0x294c, 0x77, 0xf);
    }
}
