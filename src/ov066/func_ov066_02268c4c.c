/* func_ov066_02268c4c @ 0x02268c4c, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_SetParentParameter(void (*func)(void *), int data);
extern void func_ov066_02268c18(void *argument0);
extern void func_ov066_0226686c(int status);
extern int *data_ov066_0226bdf4;

void func_ov066_02268c4c(void)
{
    int status = WM_SetParentParameter(func_ov066_02268c18, *data_ov066_0226bdf4);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}
