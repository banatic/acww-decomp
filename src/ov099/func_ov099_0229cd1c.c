/* func_ov099_0229cd1c @ 0x0229cd1c, 0x54 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(void);
extern int func_ov099_0229cf04(char *, int);
extern int func_ov099_0229cf20(char *, int);
extern int func_ov099_0229ce14(char *, int);
extern int func_ov094_0229ab90(char *, int);
extern int func_ov094_0229b328(char *, int);

int func_ov099_0229cd1c(char *a, int b)
{
    if (func_ov099_0229cf30()) {
        int r = func_ov099_0229cf04(a, b);
        return func_ov094_0229ab90(a + 0xCC, r);
    } else if (func_ov099_0229cf20(a, b)) {
        int r = func_ov099_0229ce14(a, b);
        return func_ov094_0229b328(a + 0xB2C, r);
    } else {
        return 0;
    }
}
