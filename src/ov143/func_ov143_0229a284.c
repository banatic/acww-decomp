/* func_ov143_0229a284 @ 0x0229a284, 0x20 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov143_0229a2c8(int);
extern void func_ov143_0229a2a4(int);

void func_ov143_0229a284(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov143_0229a2c8(r4);
    } else {
        func_ov143_0229a2a4(r4);
    }
}
