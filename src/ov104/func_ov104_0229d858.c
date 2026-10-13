/* func_ov104_0229d858 @ 0x0229d858, 0x50 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(int a, int b);
extern int func_ov104_0229da70(int a, int b);
extern int func_ov104_0229da38(int a, int b);
extern int func_ov094_0229b328(int a, int b);

int func_ov104_0229d858(int a, int b)
{
    if (func_ov104_0229da80(a, b) || func_ov104_0229da70(a, b)) {
        int t = func_ov104_0229da38(a, b);
        return func_ov094_0229b328(a + 0xd58, t) - 0x10;
    } else {
        if ((unsigned char) (b + 0xe1) <= 1) {
            return 0xb6;
        } else {
            return 0;
        }
    }
}
