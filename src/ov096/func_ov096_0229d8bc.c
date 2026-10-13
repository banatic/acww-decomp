/* func_ov096_0229d8bc @ 0x0229d8bc, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229d8ec(int arg);
extern int func_ov096_0229c4dc(int arg);
extern void func_0206fcb0(int ret);
extern void func_ov096_0229cc10(int arg);
extern void func_ov096_0229c2ec(int arg, int flags);

void func_ov096_0229d8bc(int arg)
{
    if (func_ov096_0229d8ec(arg) != 0) {
        func_0206fcb0(func_ov096_0229c4dc(arg));
        func_ov096_0229cc10(arg);
        func_ov096_0229c2ec(arg, 0x200);
    }
}
