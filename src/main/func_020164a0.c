/* func_020164a0 @ 0x020164a0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082fec(int, int);
extern int func_0205cb80(int);

int func_020164a0(int r0, int r1)
{
    int r5;
    int r4;
    int result;

    r5 = r0;
    r4 = r1;
    result = func_02082fec(r5, r4);
    if (result != 0) {
        return func_0205cb80(func_02082fec(r5, r4));
    }
    return 0x144;
}
