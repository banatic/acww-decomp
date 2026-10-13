/* func_0201a090 @ 0x0201a090, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201a3e8(int a, int b, int c, int d);
extern int func_0205cf28(int b);
extern int func_0205cf1c(int b);
extern void func_0201a0dc(int a, int x, int y, int c, int d);

void func_0201a090(int a, int b, int c, int d)
{
    int x, y;
    if (func_0201a3e8(a, b, c, d)) {
        x = func_0205cf28(b);
        y = func_0205cf1c(b);
        if (x == 0x16f) {
            x = 0;
        }
        if (y == 0x16f) {
            y = 0xba;
        }
        func_0201a0dc(a, x, y, c, d);
    }
}
