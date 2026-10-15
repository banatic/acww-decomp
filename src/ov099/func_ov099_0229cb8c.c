/* func_ov099_0229cb8c @ 0x0229cb8c, 0x68 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(int arg0, unsigned int arg1);
extern int func_ov099_0229cf04(int, int);
extern int func_ov099_0229cf20(int, int);
extern int func_ov099_0229ce14(int, int);
extern void func_ov099_0229cbf4(int);
extern void func_ov094_0229ab1c(int, int);
extern void func_ov094_0229b98c(int);
extern void func_ov094_0229b950(int, int);
extern void func_ov094_0229ab5c(int);

void func_ov099_0229cb8c(int r0, int r1)
{
    int r4 = r0;
    int r5 = r1;
    int temp;

    if (func_ov099_0229cf30(r0, r1)) {
        temp = func_ov099_0229cf04(r4, r5);
        func_ov094_0229ab1c(r4 + 0xcc, temp);
        func_ov094_0229b98c(r4 + 0xb2c);
    } else if (func_ov099_0229cf20(r4, r5)) {
        temp = func_ov099_0229ce14(r4, r5);
        func_ov094_0229b950(r4 + 0xb2c, temp);
        func_ov094_0229ab5c(r4 + 0xcc);
    } else {
        func_ov099_0229cbf4(r4);
    }
}
