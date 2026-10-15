/* func_ov004_02231b20 @ 0x02231b20, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02231b00(void *arg0);
extern int func_020edf70(int);

void func_ov004_02231b20(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_02231b00((void *) result);
}
