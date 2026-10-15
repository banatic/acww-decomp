/* func_ov004_0221cfe0 @ 0x0221cfe0, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221d08c(void *parameter0);
extern void func_020819ac(void *argument0);

void func_ov004_0221cfe0(void *arg0)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221d08c((void *) arg0))) != 0) {
        func_020819ac((void *) conditionInput0);
    }
}
