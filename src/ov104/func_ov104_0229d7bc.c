/* func_ov104_0229d7bc @ 0x0229d7bc, 0x40 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(int a, int b);
extern int func_ov104_0229da70(int a, int b);
extern int func_ov104_0229da38(int a, int b);
extern int func_ov094_0229b30c(int a, int b);

int func_ov104_0229d7bc(int a, int b)
{
    if (func_ov104_0229da80(a, b) != 0 || func_ov104_0229da70(a, b) != 0) {
        int t = func_ov104_0229da38(a, b);
        return func_ov094_0229b30c(a + 0xd58, t);
    }
    return 1;
}
