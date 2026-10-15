/* func_ov004_0221882c @ 0x0221882c, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022187ec(char *argument0);

void func_ov004_0221882c(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x8b8)))) {
        func_ov004_022187ec((char *) conditionInput0);
    }
}
