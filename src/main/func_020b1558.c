/* func_020b1558 @ 0x020b1558, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b15b0(void);
extern int func_020b1974(int, int);

int func_020b1558(void)
{
    int i;
    int count;
    int x;
    x = func_020b15b0();
    count = 0;
    i = count;
    do {
        if (func_020b1974(x, i) == 0) {
            count++;
        }
        i++;
    } while (i < 16);
    return count;
}
