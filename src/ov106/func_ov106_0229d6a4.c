/* func_ov106_0229d6a4 @ 0x0229d6a4, 0x20 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov106_0229d6c4(int arg);
extern void func_ov106_0229d724(int arg);

void func_ov106_0229d6a4(int arg)
{
    if (func_0206fe60() != 0) {
        func_ov106_0229d724(arg);
    } else {
        func_ov106_0229d6c4(arg);
    }
}
