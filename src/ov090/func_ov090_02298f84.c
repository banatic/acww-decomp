/* func_ov090_02298f84 @ 0x02298f84, 0x1e bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern int _s32_div_f(int, int);

int func_ov090_02298f84(int param)
{
    int result = _s32_div_f(param - 0x33, 0x19);
    if (result < 0) {
        result = 0;
    }
    if (result > 7) {
        result = 7;
    }
    return result;
}
