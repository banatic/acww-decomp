/* func_02051d08 @ 0x02051d08, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051d30(int);

int func_02051d08(unsigned short *arr, int count)
{
    int sum = 0;
    int i;
    for (i = 0; i < count; i++) {
        sum += func_02051d30(arr[i]);
    }
    return sum;
}
