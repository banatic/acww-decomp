/* func_0209de44 @ 0x0209de44, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209de88(int, int, int);
extern int func_0209de24(int, int);

int func_0209de44(int a, int b, int c, int d)
{
    int res = -1;
    int ret1;
    int t;
    int val;
    int ret2;
    ret1 = func_0209de88(a, b, 1);
    if (c < ret1) {
        t = c - ret1 + 8;
    } else {
        t = c + 1 - ret1;
    }
    val = t + 7 * (d - 1);
    ret2 = func_0209de24(a, b);
    if (val < ret2) {
        res = val;
    }
    return res;
}
