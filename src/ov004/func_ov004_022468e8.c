/* func_ov004_022468e8 @ 0x022468e8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02246828(void *arg0);
extern int func_020edf70(int);

void func_ov004_022468e8(void)
{
    int result;

    result = func_020edf70(0x58);
    if (result == 0) {
        return;
    }
    func_ov004_02246828((void *) result);
}
