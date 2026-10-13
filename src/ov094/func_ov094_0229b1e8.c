/* func_ov094_0229b1e8 @ 0x0229b1e8, 0x38 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(int a);
extern int func_02065f18(int a);

int func_ov094_0229b1e8(int a, int b)
{
    int x;
    int r;
    x = func_02065ec0(b);
    if (x == 0) {
        return -1;
    }
    r = (x - 1) * 2;
    if (func_02065f18(b) != 0xfff1) {
        r++;
    }
    return r;
}
