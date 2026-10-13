/* func_0208298c @ 0x0208298c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int);
extern int func_02082b60(int, int);

int func_0208298c(int r0, int r1)
{
    int r4 = r1;
    int r5 = r0;
    int r6 = 0;

    if (func_0207cf74(r4) != 0) {
        r4 = r5 + (r4 << 3);
        if (func_02082b60(r5, r4) != 0) {
            r6 = *(int *) r4;
        }
    }
    return r6;
}
