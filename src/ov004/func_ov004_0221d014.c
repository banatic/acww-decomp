/* func_ov004_0221d014 @ 0x0221d014, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221d08c(void *parameter0);
extern void func_020819e0(unsigned short *argument0);

void func_ov004_0221d014(void *arg0)
{
    unsigned short *conditionInput0;

    if ((conditionInput0 = (unsigned short *) (func_ov004_0221d08c((void *) arg0))) != 0) {
        func_020819e0((unsigned short *) conditionInput0);
    }
}
