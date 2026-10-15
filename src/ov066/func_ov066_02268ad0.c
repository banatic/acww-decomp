/* func_ov066_02268ad0 @ 0x02268ad0, 0x34 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_EndParent(void (*)(void *));
extern void func_ov066_0226686c(int status);
extern void func_ov066_02268a60(void *argument0);

void func_ov066_02268ad0(void)
{
    int status = WM_EndParent((void (*)(void *)) func_ov066_02268a60);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}
