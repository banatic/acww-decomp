/* func_02083274 @ 0x02083274, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205ec50(void *a, int b, int c, int d, int e, int f);

void func_02083274(char *p, int b, int c)
{
    func_0205ec50(p + 4, b, 0, c, 0, 0);
    *p = 1;
}
