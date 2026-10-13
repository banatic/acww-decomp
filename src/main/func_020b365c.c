/* func_020b365c @ 0x020b365c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int, int);

int func_020b365c(int a, int b, int c)
{
    int d = c - b;
    return b + FX_MulFunc(a, d, c);
}
