/* func_ov100_0229d8b0 @ 0x0229d8b0, 0x20 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov100_0229d90c(int);
extern void func_ov100_0229d8d0(int);

void func_ov100_0229d8b0(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov100_0229d90c(r4);
    } else {
        func_ov100_0229d8d0(r4);
    }
}
