/* func_ov066_0226853c @ 0x0226853c, 0x34 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int WM_EndMP(void (*)(void));
extern void func_ov066_022684c4(void);
extern void func_ov066_0226686c(void);

void func_ov066_0226853c(void)
{
    if (WM_EndMP(func_ov066_022684c4) == 2) {
        return;
    }
    func_ov066_0226686c();
}
