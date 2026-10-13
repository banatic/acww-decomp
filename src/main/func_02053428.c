/* func_02053428 @ 0x02053428, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02053450(int a0, int a1, int a2, int a3);

int func_02053428(int a0, int a1, int a2, int a3)
{
    if (a1 < 4) {
        return func_02053450(a0 + 20 * a1, a2, a3, a3);
    } else {
        return 1;
    }
}
