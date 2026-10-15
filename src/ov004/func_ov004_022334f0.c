/* func_ov004_022334f0 @ 0x022334f0, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022334d0(void *arg0);
extern int func_020edf70(int);

void func_ov004_022334f0(void)
{
    int result;

    result = func_020edf70(0x54);
    if (result == 0) {
        return;
    }
    func_ov004_022334d0((void *) result);
}
