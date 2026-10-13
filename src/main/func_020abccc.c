/* func_020abccc @ 0x020abccc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020abccc(unsigned char *arg)
{
    unsigned int value;
    value = *(unsigned int *) (arg + 0x13C);
    if ((value - 6) > 5) {
        return 0;
    }
    return 1;
}
