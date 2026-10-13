/* func_ov003_0222a378 @ 0x0222a378, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_0222a378(char *self)
{
    int r = 2;
    int v;
    v = *(int *) (self + 0x120) >> 17;
    if (v == 0) {
        r = 0;
    } else if (v == 5) {
        r = 1;
    }
    return r;
}
