/* func_ov066_022688cc @ 0x022688cc, 0x40 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_02268878(void);
extern int WM_Disconnect(void (*cb)(void), int arg);
extern void func_ov066_0226686c(void);

int func_ov066_022688cc(int param)
{
    if (WM_Disconnect(func_ov066_02268878, param) == 2) {
        return 1;
    } else {
        func_ov066_0226686c();
        return 0;
    }
}
