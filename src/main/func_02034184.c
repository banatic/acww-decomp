/* func_02034184 @ 0x02034184, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034184(int *r0, int r1);

int func_02034184(int *r0, int r1)
{
    if (r0[12] != 0) {
        if (r1 > r0[15]) {
            return 0;
        }
        return 1;
    } else {
        return 0;
    }
}
