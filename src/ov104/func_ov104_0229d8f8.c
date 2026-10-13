/* func_ov104_0229d8f8 @ 0x0229d8f8, 0x40 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(char *a, int b);
extern int func_ov104_0229da70(char *a, int b);
extern int func_ov104_0229da38(char *a, int b);
extern int func_ov094_0229b8d8(char *a, int b);

int func_ov104_0229d8f8(char *a, int b)
{
    if (func_ov104_0229da80(a, b) != 0 || func_ov104_0229da70(a, b) != 0) {
        return func_ov094_0229b8d8(a + 0xd58, func_ov104_0229da38(a, b));
    } else {
        return 0;
    }
}
