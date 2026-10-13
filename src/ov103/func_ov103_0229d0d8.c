/* func_ov103_0229d0d8 @ 0x0229d0d8, 0x44 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(int data);
extern void func_ov002_022096d8(int data, int val);
extern int func_0208e4bc(int data);
extern void func_ov103_0229c6a0(int data);
extern void func_ov002_02208098(int data, int val);

void func_ov103_0229d0d8(int param)
{
    if (func_ov002_0220909c(param + 0x22d8)) {
        func_ov002_022096d8(param + 0x22d8, 0);
        if (func_0208e4bc(param + 0x2274)) {
            func_ov103_0229c6a0(param);
        }
        func_ov002_02208098(param, 0x16);
    }
}
