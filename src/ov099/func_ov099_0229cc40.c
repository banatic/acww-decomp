/* func_ov099_0229cc40 @ 0x0229cc40, 0x34 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(char *a, int b);
extern int func_ov099_0229cf04(char *a, int b);
extern int func_ov094_0229aaac(char *ptr, int val);

int func_ov099_0229cc40(char *a, int b)
{
    if (func_ov099_0229cf30(a, b) != 0) {
        return func_ov094_0229aaac(a + 0xcc, func_ov099_0229cf04(a, b));
    }
    return 0x0000fff1;
}
