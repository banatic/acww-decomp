/* func_02036020 @ 0x02036020, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02036020(char arr[8][16])
{
    int i;
    int value;
    i = 0;
    value = i;
    do {
        arr[i][4] = value;
        i++;
    } while (i < 8);
}
