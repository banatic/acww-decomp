/* func_0207a2d8 @ 0x0207a2d8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int);

int func_0207a2d8(int r0, int r1, int r2)
{
    int r4 = 0;
    int r5 = r1;
    int r6 = r0;
    int r7 = r2;

    if (func_0207cf74(r5) != 0) {
        *(unsigned char *) (r6 + r5) = (unsigned char) r7;
        r4 = 1;
    }

    return r4;
}
