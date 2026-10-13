/* func_02039ebc @ 0x02039ebc, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02039ebc(int arg0)
{
    int *ptr;
    int result;
    int *field;

    ptr = (int *) (arg0 + 0xa4);
    if (*ptr != 0) {
        result = 1;
    } else {
        result = 0;
    }
    if (result != 0) {
        field = (int *) (arg0 + 0xb0);
        *field = 0;
    }
    return result;
}
