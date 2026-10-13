/* func_02075240 @ 0x02075240, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int (*data_020ccff0[])(int, int, int);

int func_02075240(int a, int b, int c, int index)
{
    return data_020ccff0[index](a, b, c);
}
