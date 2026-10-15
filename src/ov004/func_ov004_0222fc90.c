/* func_ov004_0222fc90 @ 0x0222fc90, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020edf70(unsigned int size);
extern void *func_ov004_0222fc3c(char *argument0);

void func_ov004_0222fc90(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x620)))) {
        func_ov004_0222fc3c((char *) conditionInput0);
    }
}
