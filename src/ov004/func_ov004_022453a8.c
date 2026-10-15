/* func_ov004_022453a8 @ 0x022453a8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02245390(void *arg0);
extern int func_020edf70(int);

void func_ov004_022453a8(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_02245390((void *) result);
}
