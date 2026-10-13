/* func_0203e0a8 @ 0x0203e0a8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961a8(int);
extern int func_0203efbc(int);
extern int func_0203e478(int, int, int, int, int);

int func_0203e0a8(int arg0, int arg1)
{
    int tmp1;
    int tmp2;
    if (arg1 == 0) {
        tmp1 = func_0203efbc(func_020961a8(4));
        tmp2 = func_0203efbc(arg0);
        return func_0203e478(tmp1, tmp2, 6, 3, 0);
    } else {
        return 0;
    }
}
