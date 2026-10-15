/* func_ov066_0226848c @ 0x0226848c, 0x38 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_02268458(void *argument0);
extern int WM_SetEntry(void (*callback)(void *), int arg);
extern void func_ov066_0226686c(int status);

void func_ov066_0226848c(int arg)
{
    int status = WM_SetEntry(func_ov066_02268458, arg);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}
