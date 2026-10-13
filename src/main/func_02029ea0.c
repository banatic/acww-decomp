/* func_02029ea0 @ 0x02029ea0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02029ebc(void);

int func_02029ea0(int r0, int r1)
{
    int r4 = r1;
    if (func_02029ebc() != 0 && r4 == 0) {
        return 1;
    }
    return 0;
}
