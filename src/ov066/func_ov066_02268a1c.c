/* func_ov066_02268a1c @ 0x02268a1c, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_StartConnectEx(void (*func)(void), int arg, int a, int b, int c);
extern void func_ov066_0226890c(void);
extern void func_ov066_0226686c(void);

void func_ov066_02268a1c(int arg)
{
    if (WM_StartConnectEx(func_ov066_0226890c, arg, 0, 1, 0) == 2) {
        return;
    }
    func_ov066_0226686c();
}
