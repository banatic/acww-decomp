/* func_02098844 @ 0x02098844, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020988d8(int);

int func_02098844(int r0, int r1)
{
    int r4 = 0;
    int r5 = r0;
    int r6 = r1;

    if (func_020988d8(r6) != 0) {
        r4 = r5 + r6 * 0x249c;
    }

    return r4;
}
