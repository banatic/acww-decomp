/* func_ov004_02230c7c @ 0x02230c7c, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020edf70(unsigned int size);
extern void *func_ov004_02230bf8(char *argument0);

void func_ov004_02230c7c(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x6dc)))) {
        func_ov004_02230bf8((char *) conditionInput0);
    }
}
