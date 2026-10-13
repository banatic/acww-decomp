/* func_ov120_0229ad5c @ 0x0229ad5c, 0x68 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov120_0229a438(int a, int b);
extern void func_0206fdd4(int a, int b, int c, int d, int e, int f);

void func_ov120_0229ad5c(int a, int b)
{
    func_ov120_0229a438(a, 0x80);
    if (b == 14) {
        func_0206fdd4(a + 0x1720, 0x13, 0, 0x1c, 0x19, 4);
    } else if (b == 13) {
        func_0206fdd4(a + 0x1720, 0x13, 0, 0x1c, 7, 3);
    } else {
        int x = b * 2;
        func_0206fdd4(a + 0x1720, 0x13, x, 0x1c, x + 1, 3);
    }
}
