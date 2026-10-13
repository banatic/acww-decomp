/* func_020121f8 @ 0x020121f8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082c98(int *p);

int func_020121f8(int *p)
{
    int *q = p + 1;
    int r = func_02082c98(q);
    if (r) {
        return *(int *) (r + 4);
    }
    return 0;
}
