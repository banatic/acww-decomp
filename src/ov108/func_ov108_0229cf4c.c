/* func_ov108_0229cf4c @ 0x0229cf4c, 0x20 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov108_0229cfa8(int);
extern void func_ov108_0229cf6c(int);

void func_ov108_0229cf4c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov108_0229cfa8(r4);
    } else {
        func_ov108_0229cf6c(r4);
    }
}
