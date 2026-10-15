/* func_02029e18 @ 0x02029e18, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02029e34(unsigned short *);

int func_02029e18(unsigned short *param1, int param2)
{
    int result;
    if (func_02029e34((unsigned short *) param1) != 0 && param2 == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
