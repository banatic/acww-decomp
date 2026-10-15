/* func_02048e34 @ 0x02048e34, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204edd0(int, int, int);

int func_02048e34(int argument0, int argument1, int argument2)
{
    int r4 = 0;
    if (func_0204edd0((int) argument0, (int) argument1, (int) argument2) != 0) {
        r4 = 1;
    }
    return r4;
}
