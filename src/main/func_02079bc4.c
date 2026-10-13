/* func_02079bc4 @ 0x02079bc4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int);
extern int func_02079c74(int, int, int);
extern void func_02079c00(int, int, int);

void func_02079bc4(int a, int b, int c, int d)
{
    if (func_0207cf74(b) != 0 && func_0207cf74(c) != 0) {
        func_02079c00(a, func_02079c74(a, b, c), d);
    }
}
