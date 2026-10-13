/* func_ov099_0229cb20 @ 0x0229cb20, 0x50 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(int a, int b);
extern int func_ov099_0229cf04(int a, int b);
extern int func_ov099_0229cf20(int a, int b);
extern int func_ov099_0229ce14(int a, int b);
extern void func_ov094_0229aafc(int a, int b);
extern void func_ov094_0229b938(int a, int b);

void func_ov099_0229cb20(int a, int b)
{
    if (func_ov099_0229cf30(a, b)) {
        func_ov094_0229aafc(a + 0xcc, func_ov099_0229cf04(a, b));
    } else {
        if (func_ov099_0229cf20(a, b)) {
            func_ov094_0229b938(a + 0xb2c, func_ov099_0229ce14(a, b));
        }
    }
}
