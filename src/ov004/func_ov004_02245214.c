/* func_ov004_02245214 @ 0x02245214, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022451fc(void);
extern int func_020edf70(int);

void func_ov004_02245214(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_022451fc();
}
