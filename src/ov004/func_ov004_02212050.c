/* func_ov004_02212050 @ 0x02212050, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_0221202c(void *argument0);

void func_ov004_02212050(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x850)))) {
        func_ov004_0221202c((void *) conditionInput0);
    }
}
