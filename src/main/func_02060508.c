/* func_02060508 @ 0x02060508, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02060508(int a, int b)
{
    int *p;
    if (b >= 4) {
        return 0;
    }
    p = *(int **) (a + (b << 2) + 0x750);
    if (p != 0 && p[1] == 4) {
        return (int) p;
    }
    return 0;
}
