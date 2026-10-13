/* func_0208c5f0 @ 0x0208c5f0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0208c5f0(int *param)
{
    int r0;
    int r1;
    int r2;

    r0 = (int) param + 0xc0;
    r1 = *(int *) r0;
    if (r1 == 2) {
        r2 = 1;
    } else {
        r2 = 0;
    }
    r0 = 0;
    if (r1 == 0) {
        r0 = 1;
    } else if (r2 != 0) {
        r0 = 1;
    }
    return r0;
}
