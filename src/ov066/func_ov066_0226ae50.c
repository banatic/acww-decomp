/* func_ov066_0226ae50 @ 0x0226ae50, 0x68 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_0226adcc(void);
extern void func_ov066_0226686c(void);
extern int WM_SetMPDataToPortEx(int (*func)(void), int e, int b, int c, int d, int a, int two);

int func_ov066_0226ae50(int a, int b, int c, int d, int e)
{
    int result = WM_SetMPDataToPortEx(func_ov066_0226adcc, e, b, c, d, a, 2);
    if (result != 2 && result != 7) {
        func_ov066_0226686c();
        return 0;
    }
    return 1;
}
