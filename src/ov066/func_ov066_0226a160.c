/* func_ov066_0226a160 @ 0x0226a160, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_0226a074(void);
extern void func_ov066_0226686c(void);
extern int WM_MeasureChannel(void (*f)(void), int a, int b, int c, int d);

int func_ov066_0226a160(int param)
{
    if (WM_MeasureChannel(func_ov066_0226a074, 3, 17, param, 30) == 2) {
        return 1;
    }
    func_ov066_0226686c();
    return 0;
}
