/* func_ov099_0229cd70 @ 0x0229cd70, 0x54 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(void *a, void *b);
extern int func_ov099_0229cf04(void *a, void *b);
extern int func_ov099_0229cf20(void *a, void *b);
extern int func_ov099_0229ce14(void *a, void *b);
extern int func_ov094_0229aba4(void *a, int x);
extern int func_ov094_0229b384(void *a, int x);

int func_ov099_0229cd70(void *a, void *b)
{
    if (func_ov099_0229cf30(a, b)) {
        int x = func_ov099_0229cf04(a, b);
        a = (char *) a + 0xcc;
        return func_ov094_0229aba4(a, x);
    }
    if (func_ov099_0229cf20(a, b)) {
        int y = func_ov099_0229ce14(a, b);
        return func_ov094_0229b384((char *) a + 0xb2c, y);
    }
    return 0;
}
