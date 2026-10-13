/* func_02003ea0 @ 0x02003ea0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020c7590[];
extern unsigned int data_020c75c0[];

unsigned int func_02003ea0(void)
{
    unsigned int max = 0;
    unsigned int *p = data_020c7590;

    while (p < data_020c75c0) {
        if (*p > max) {
            max = *p;
        }
        p++;
    }

    return (max + 3) & ~3;
}
