/* func_0203e0e0 @ 0x0203e0e0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203efbc(int);
extern int func_0203e478(int, int, int, int, int);

int func_0203e0e0(int a, int b)
{
    int result1 = 0;
    if (b != 0) {
        result1 = func_0203efbc(b);
    }
    return func_0203e478(func_0203efbc(a), result1, 2, 3, 0);
}
