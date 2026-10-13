/* func_ov104_0229d8a8 @ 0x0229d8a8, 0x50 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(int a, int b);
extern int func_ov104_0229da70(int a, int b);
extern int func_ov104_0229da38(int a, int b);
extern int func_ov094_0229b384(int a, int b);

int func_ov104_0229d8a8(int a, int b)
{
    if (func_ov104_0229da80(a, b) != 0 || func_ov104_0229da70(a, b) != 0) {
        return func_ov094_0229b384(a + 0xd58, func_ov104_0229da38(a, b));
    } else {
        if (b == 0x1f) {
            return 0xbc;
        } else if (b == 0x20) {
            return 0x74;
        } else {
            return 0;
        }
    }
}
