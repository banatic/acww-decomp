/* func_0201a6f8 @ 0x0201a6f8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0201a6f8(int *a)
{
    int res = -1;
    int i;

    for (i = 0; i < 4; i++) {
        if (a[i] == -1) {
            res = i;
            break;
        }
    }

    return res;
}
