/* func_ov066_0226848c @ 0x0226848c, 0x38 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_02268458(void);
extern int WM_SetEntry(int (*callback)(void), int arg);
extern void func_ov066_0226686c(void);

void func_ov066_0226848c(int arg)
{
    if (WM_SetEntry(func_ov066_02268458, arg) == 2) {
        return;
    }
    func_ov066_0226686c();
}
