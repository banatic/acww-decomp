/* func_ov143_0229a2e0 @ 0x0229a2e0, 0x20 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov143_0229a31c(int);
extern void func_ov143_0229a300(int);

void func_ov143_0229a2e0(int param)
{
    int r4 = param;
    if (func_0206fe60() != 0) {
        func_ov143_0229a31c(r4);
    } else {
        func_ov143_0229a300(r4);
    }
}
