/* func_0203e070 @ 0x0203e070, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961a8(int);
extern int func_0203efbc(int);
extern int func_0203e478(int, int, int, int, int);

int func_0203e070(int a, int b)
{
    int x;
    int y;

    if (b == 0) {
        x = func_0203efbc(func_020961a8(4));
        y = func_0203efbc(a);
        return func_0203e478(x, y, 7, 3, 0);
    }
    return 0;
}
