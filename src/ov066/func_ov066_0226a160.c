/* func_ov066_0226a160 @ 0x0226a160, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_0226a074(void *argument0);
extern void func_ov066_0226686c(int status);
extern int WM_MeasureChannel(void (*f)(void *), int a, int b, int c, int d);

int func_ov066_0226a160(int param)
{
    int status = WM_MeasureChannel((void (*)(void *)) func_ov066_0226a074, 3, 17, param, 30);
    if (status == 2) {
        return 1;
    }
    func_ov066_0226686c(status);
    return 0;
}
