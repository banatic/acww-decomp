/* func_ov066_0226af04 @ 0x0226af04, 0x38 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int data_ov066_0226be08;
extern void func_ov066_0226b3d0(void);

void func_ov066_0226af04(void)
{
    if (*(signed char *) (*(int *) &data_ov066_0226be08 + 2) >= 2) {
        return;
    }
    func_ov066_0226b3d0();
}
