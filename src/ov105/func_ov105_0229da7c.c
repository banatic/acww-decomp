/* func_ov105_0229da7c @ 0x0229da7c, 0x20 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov105_0229dafc(int);
extern void func_ov105_0229da9c(int);

void func_ov105_0229da7c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov105_0229dafc(r4);
    } else {
        func_ov105_0229da9c(r4);
    }
}
