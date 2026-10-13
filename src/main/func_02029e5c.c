/* func_02029e5c @ 0x02029e5c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02029e78(int a, int b);

int func_02029e5c(int a, int b)
{
    if (func_02029e78(a, b) != 0 && b == 0) {
        return 1;
    } else {
        return 0;
    }
}
