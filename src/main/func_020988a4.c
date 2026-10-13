/* func_020988a4 @ 0x020988a4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020988d8(int);
extern int func_02099a28(int);

int func_020988a4(int r5, int r4)
{
    int r0;
    int r1;

    r1 = r4;
    r0 = func_020988d8(r1);
    if (r0 != 0) {
        r4 = r4 * 0x249c;
        r0 = r5 + r4;
        r0 = func_02099a28(r0);
        if (r0 != 0) {
            return 1;
        }
    }
    return 0;
}
