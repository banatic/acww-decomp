/* func_02060f04 @ 0x02060f04, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67e8(int);
extern int func_020b6818(int);
extern int func_02060ee0(int, int);

int func_02060f04(int r0, int r1)
{
    int r4;
    int r5;
    int result;

    r5 = r0;
    r4 = r1;

    if (func_020b67e8(r4) != 0) {
        result = func_02060ee0(r5, func_020b6818(r4));
    } else {
        result = 0;
    }

    return result;
}
