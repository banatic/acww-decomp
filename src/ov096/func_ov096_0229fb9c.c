/* func_ov096_0229fb9c @ 0x0229fb9c, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov096_0229fbf0(int);
extern void func_ov096_0229fbbc(int);

void func_ov096_0229fb9c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov096_0229fbf0(r4);
    } else {
        func_ov096_0229fbbc(r4);
    }
}
