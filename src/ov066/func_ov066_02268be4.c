/* func_ov066_02268be4 @ 0x02268be4, 0x34 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_StartParent(void (*)(void *));
extern void func_ov066_02268b04(void *argument0);
extern void func_ov066_0226686c(int status);

void func_ov066_02268be4(void)
{
    int status = WM_StartParent((void (*)(void *)) func_ov066_02268b04);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}
