/* func_0200be34 @ 0x0200be34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(int);
extern int func_0200c3b0(int, int, int, int);

int func_0200be34(int r0)
{
    int r4 = r0;
    int r1;
    int r2;
    int r3;

    if (func_02056f94(r4 + 0x2d0) != 0) {
        r1 = 5;
        r2 = r1;
        r3 = 0;
        r3 = ~r3;
        func_0200c3b0(r4, r1, r2, r3);
    }
    return;
}
