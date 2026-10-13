/* func_ov004_0224551c @ 0x0224551c, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022454dc(void);
extern int func_020edf70(int);

void func_ov004_0224551c(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_022454dc();
}
