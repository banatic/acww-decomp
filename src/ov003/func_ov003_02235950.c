/* func_ov003_02235950 @ 0x02235950, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, int c);
extern int func_02031b5c(int a, int b);

int func_ov003_02235950(int p)
{
    int x = 0;
    int y = 0;

    func_0204f818(&x, &y, p);
    if (func_02031b5c(x, y) != 0) {
        return 1;
    }
    return 0;
}
