/* func_0209d8b0 @ 0x0209d8b0, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d918(int a, int b);

int func_0209d8b0(int a, unsigned int b, int c)
{
    if (b < 0x33) {
        return func_0209d918(a + b, c);
    }
    return 0;
}
