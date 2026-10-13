/* func_02049fbc @ 0x02049fbc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern int func_02049ff0(void);

int func_02049fbc(int a, int *p)
{
    int result = 0;
    int x = p[0];
    int y = p[1];
    int high1 = x >> 4;
    int high2 = y >> 4;
    int low2 = y - (high2 << 4);

    if (func_0204f5e0(a, high1, high2, x - (high1 << 4), low2, result)) {
        result = func_02049ff0();
    }
    return result;
}
