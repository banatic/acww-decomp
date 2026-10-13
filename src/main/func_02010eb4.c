/* func_02010eb4 @ 0x02010eb4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c798c[];

int func_02010eb4(int a1, int *a2)
{
    if (data_020c798c[*a2] != 0) {
        return 2;
    } else {
        return 0;
    }
}
