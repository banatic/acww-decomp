/* func_ov068_02266a24 @ 0x02266a24, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02227638(int);
extern int func_ov068_02266a70(int, int, int, int, int);

int func_ov068_02266a24(int a, int b, int *out, int c, int d)
{
    int i = 0;
    int id = i;
    int ret;

    for (; i < 6; i++) {
        ret = func_ov003_02227638(i);
        if (ret != ~id) {
            if (func_ov068_02266a70(a, b, i, c, d)) {
                *out = i;
                return ret;
            }
        }
    }
    return -1;
}
