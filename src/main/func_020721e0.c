/* func_020721e0 @ 0x020721e0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002628(int a, int b, int c, int d, int e);

int func_020721e0(int a, int b, int c)
{
    if (c < 0 || c >= 8) {
        return 0;
    }
    func_02002628(a, b, c << 2, 4, 4);
    return 1;
}
