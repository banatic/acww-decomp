/* func_020b4178 @ 0x020b4178, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050bdc_unk(int, int);

int func_020b4178(int a, int b)
{
    int ret = 0;
    int res;
    if (a == b) {
        ret = 1;
    } else {
        res = func_02050bdc_unk(a, b);
        if (res == b) {
            ret = 1;
        }
    }
    return ret;
}
