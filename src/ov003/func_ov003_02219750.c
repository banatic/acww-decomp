/* func_ov003_02219750 @ 0x02219750, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_ov003_022195c8(int, int, int, int);

int func_ov003_02219750(int a)
{
    int r;
    r = func_02096718(4);
    if (r) {
        return func_ov003_022195c8(r, a, 5, -1);
    } else {
        return 0;
    }
}
