/* func_0203e3c8 @ 0x0203e3c8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961a8(int);
extern int func_0203efbc(int);
extern int func_0203e478(int, int, int, int, int);

int func_0203e3c8(int param)
{
    int temp;

    temp = func_020961a8(4);
    if (temp == 0) {
        return 0;
    }
    return func_0203e478(0, func_0203efbc(temp), 1, 2, param);
}
