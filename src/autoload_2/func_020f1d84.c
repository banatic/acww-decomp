/* func_020f1d84 @ 0x020f1d84, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eef70(void);
extern int func_0210e198(int, int);

int func_020f1d84(int a, int b)
{
    int r0;
    r0 = func_020eef70();
    return func_0210e198(b, r0);
}
