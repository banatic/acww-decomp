/* func_ov002_02207ee8 @ 0x02207ee8, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022084e4(char *arg0, int arg1, int arg2, int arg3, int arg4);

void func_ov002_02207ee8(char *a, int b, int c, int d, int e)
{
    if (c == 0) {
        c = 4;
    }
    func_ov002_022084e4(a + 0x70, b, c, d, e);
}
