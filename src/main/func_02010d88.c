/* func_02010d88 @ 0x02010d88, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02089b80(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

void func_02010d88(int a, int b, int c, int d)
{
    int stack[6];

    stack[0] = d;
    stack[1] = 0x11;
    stack[2] = 0x2c;
    stack[3] = 0;
    stack[4] = 0xff;
    stack[5] = 0x1000;

    func_02089b80(a + 0x1c4, a, b, c, stack[0], stack[1], stack[2], stack[3], stack[4], stack[5]);
}
