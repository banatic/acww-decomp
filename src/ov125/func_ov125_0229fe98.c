/* func_ov125_0229fe98 @ 0x0229fe98, 0x20 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov125_0229fee4(int);
extern void func_ov125_0229feb8(int);

void func_ov125_0229fe98(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov125_0229fee4(r4);
    } else {
        func_ov125_0229feb8(r4);
    }
}
