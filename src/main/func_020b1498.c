/* func_020b1498 @ 0x020b1498, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b15b0(void);
extern int func_020b1974(int, int);

int func_020b1498(int p)
{
    int a = func_020b15b0();
    if (func_020b1974(a, p) == 0) {
        return 0;
    } else {
        return a + 74 * p;
    }
}
