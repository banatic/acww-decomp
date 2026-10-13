/* func_ov141_02299f94 @ 0x02299f94, 0x34 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

int func_ov141_02299f94(int *r0, int r1)
{
    int r2;
    int r3;

    r2 = (r0[0x49c] == r1) ? 0 : 1;
    r0[0x49c] = r1;
    if (r1 == -1) {
        r0[0x49d] = 9;
    } else {
        r0[0x49d] = 8;
    }
    return r2;
}
