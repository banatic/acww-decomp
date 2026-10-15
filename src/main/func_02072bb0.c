/* func_02072bb0 @ 0x02072bb0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072b64(int, int);

int func_02072bb0(int r0, int index)
{
    int r4 = r0;
    int r0_2 = func_02072b64(r4 + 0x11a0, index);
    return r4 + r0_2 * 0x234;
}
