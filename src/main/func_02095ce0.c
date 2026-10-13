/* func_02095ce0 @ 0x02095ce0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_0200c9a8(int, int, int, int);

int func_02095ce0(void)
{
    int res = func_02096718(4);
    if (res != 0) {
        return func_0200c9a8(res, 3, 5, -1);
    }
    return 0;
}
