/* func_ov128_0229be00 @ 0x0229be00, 0x20 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov128_0229be44(int);
extern void func_ov128_0229be20(int);

void func_ov128_0229be00(int r0)
{
    if (func_0206fe60() != 0) {
        func_ov128_0229be44(r0);
    } else {
        func_ov128_0229be20(r0);
    }
}
