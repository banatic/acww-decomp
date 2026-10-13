/* func_02091444 @ 0x02091444, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02091444(int param1, int param2, int param3, int param4);

int func_02091444(int param1, int param2, int param3, int param4)
{
    int i;
    int result;
    int *ptr;

    result = 0;
    i = 0;
    ptr = (int *) param3;

    while (i < param4) {
        if (param2 == *(ptr + 5)) {
            result = (int) ptr;
            break;
        }
        ptr = (int *) ((char *) ptr + 0x1c);
        i++;
    }

    return result;
}
