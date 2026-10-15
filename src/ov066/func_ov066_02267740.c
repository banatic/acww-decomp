/* func_ov066_02267740 @ 0x02267740, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_StartScan(void (*func)(void *), int data);
extern void func_ov066_022676a0(void *argument0);
extern void func_ov066_0226686c(int status);
extern int *data_ov066_0226bdf0;

void func_ov066_02267740(void)
{
    int status = WM_StartScan(func_ov066_022676a0, *data_ov066_0226bdf0);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}
