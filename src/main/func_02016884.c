/* func_02016884 @ 0x02016884, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020168ac(int param, int, int);
extern int func_020164a0(int param, int param2);

int func_02016884(int param, int a, int b)
{
    a = func_020168ac(param, a, b);
    b = func_020164a0(param, 0);
    if (a == b) {
        return 1;
    } else {
        return 0;
    }
}
