/* func_0208016c @ 0x0208016c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807a8(int, int, int);
extern int func_02081b68(int, int, int);

int func_0208016c(int a1, int a2, int a3, int a4)
{
    int r = func_020807a8(a1, a4, a3);
    if (r) {
        r = func_02081b68(r, a2, a3);
    }
    return r;
}
