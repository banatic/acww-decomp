/* func_ov109_0229cd9c @ 0x0229cd9c, 0x20 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov109_0229cdf8(int);
extern void func_ov109_0229cdbc(int);

void func_ov109_0229cd9c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov109_0229cdf8(r4);
    } else {
        func_ov109_0229cdbc(r4);
    }
}
