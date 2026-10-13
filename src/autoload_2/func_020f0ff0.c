/* func_020f0ff0 @ 0x020f0ff0, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int *func_020f0ff0(int *p);

int *func_020f0ff0(int *p)
{
    int *q;
    q = (int *) *p;
    if (q != 0) {
        return q + 5;
    } else {
        return 0;
    }
}
