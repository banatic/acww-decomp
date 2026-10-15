/* func_ov004_0223c984 @ 0x0223c984, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#define g_x0 (*(int *) 0xffffc000)
extern int func_ov004_0223c9b4(int, int);

int func_ov004_0223c984(int p0)
{
    return func_ov004_0223c9b4(p0, (int) &g_x0);
}
