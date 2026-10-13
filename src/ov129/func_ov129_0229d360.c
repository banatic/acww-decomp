/* func_ov129_0229d360 @ 0x0229d360, 0x20 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern int func_ov129_0229d3e0(int);
extern int func_ov129_0229d380(int);

int func_ov129_0229d360(int param)
{
    int result;
    if (func_0206fe60() != 0) {
        result = func_ov129_0229d3e0(param);
    } else {
        result = func_ov129_0229d380(param);
    }
    return result;
}
