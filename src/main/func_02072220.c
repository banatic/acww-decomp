/* func_02072220 @ 0x02072220, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002628(int, int, int, int, int);

int func_02072220(int a, int b, int c)
{
    if (c < 0 || c >= 8) {
        return 0;
    }
    func_02002628(a, b, c * 4, 4, 4);
    return 1;
}
