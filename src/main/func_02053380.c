/* func_02053380 @ 0x02053380, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020533ac(int a, int b, int c, int d);
extern int func_02053428(int, int, int, int);

int func_02053380(int a1, int a2, int a3, int a4)
{
    int result;

    if (func_020533ac(a1, a2, a3, a4)) {
        result = func_02053428(a1, a2, a3, a4);
    } else {
        result = 0;
    }
    return result;
}
