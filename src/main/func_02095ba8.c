/* func_02095ba8 @ 0x02095ba8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_0200c904(int, unsigned short, int, int, int, int);

int func_02095ba8(unsigned short *a, int b, int c)
{
    int res = func_02096718(4);
    if (res != 0) {
        return func_0200c904(res, *a, b, c, 6, -1);
    } else {
        return 0;
    }
}
