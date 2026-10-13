/* func_ov066_02267740 @ 0x02267740, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_StartScan(int (*func)(void), int data);
extern int func_ov066_022676a0(void);
extern void func_ov066_0226686c(void);
extern int *data_ov066_0226bdf0;

void func_ov066_02267740(void)
{
    if (WM_StartScan(func_ov066_022676a0, *data_ov066_0226bdf0) == 2) {
        return;
    }
    func_ov066_0226686c();
}
