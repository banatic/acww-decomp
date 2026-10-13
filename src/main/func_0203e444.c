/* func_0203e444 @ 0x0203e444, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203efbc(void);
extern int func_0203e478(int, int, int, int, unsigned char);

int func_0203e444(int a, int b)
{
    int x;
    if (b < 0) {
        return 0;
    }
    x = 0;
    if (a != 0) {
        x = func_0203efbc();
    }
    return func_0203e478(x, 0, 3, 1, (unsigned char) b);
}
