/* func_02039edc @ 0x02039edc, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02039edc(int arg0)
{
    int val;
    int val2;

    val = *(int *) (arg0 + 0xa4);
    if (val == 0) {
        val2 = 1;
    } else {
        val2 = 0;
    }
    if (val2 != 0) {
        *(int *) (arg0 + 0xb0) = 2;
    }
    return val2;
}
