/* func_02041110 @ 0x02041110, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02041110(int a, int *array, int b)
{
    int i;
    int result;
    int *p = array;
    int count = func_020644cc(b);
    i = 0;
    result = -1;
    while (i < 5) {
        if (*p == 1) {
            count--;
            if (count < 0) {
                result = i;
                break;
            }
        }
        p++;
        i++;
    }
    return result;
}
