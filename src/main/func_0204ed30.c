/* func_0204ed30 @ 0x0204ed30, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *p1, int *p2, int p3);
extern void func_0204ed58(int a, int b, int c);

void func_0204ed30(int a, int b)
{
    int x = 0;
    int y = 0;
    func_0204f818(&x, &y, b);
    func_0204ed58(a, x, y);
}
