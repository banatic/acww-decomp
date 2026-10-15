/* func_ov066_0226853c @ 0x0226853c, 0x34 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_EndMP(void (*)(void *));
extern void func_ov066_022684c4(void *argument0);
extern void func_ov066_0226686c(int status);

void func_ov066_0226853c(void)
{
    int status = WM_EndMP((void (*)(void *)) func_ov066_022684c4);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}
