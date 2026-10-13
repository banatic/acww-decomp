/* func_0209d8cc @ 0x0209d8cc, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d970(int, int);

int func_0209d8cc(int a, unsigned int b, int c)
{
    if (b >= 0x33) {
        return a;
    }
    return func_0209d970(a + b, c);
}
