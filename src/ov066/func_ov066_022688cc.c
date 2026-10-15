/* func_ov066_022688cc @ 0x022688cc, 0x40 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_02268878(void *argument0);
extern int WM_Disconnect(void (*cb)(void *), int arg);
extern void func_ov066_0226686c(int status);

int func_ov066_022688cc(int param)
{
    int status = WM_Disconnect((void (*)(void *)) func_ov066_02268878, param);
    if (status == 2) {
        return 1;
    } else {
        func_ov066_0226686c(status);
        return 0;
    }
}
