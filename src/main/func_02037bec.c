/* func_02037bec @ 0x02037bec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ca008[];

int func_02037bec(int value)
{
    register int *ptr = data_020ca008;
    unsigned int i;
    for (i = 0; i < 55; i++) {
        if (value == *ptr++) {
            return (int) i;
        }
    }
    return 54;
}
