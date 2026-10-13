/* func_ov102_0229d034 @ 0x0229d034, 0x40 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(int, int);
extern int func_ov102_0229d454(int, int);
extern int func_ov102_0229d400(int, int);
extern int func_ov094_0229aaac(int, int);

int func_ov102_0229d034(int a, int b)
{
    int result;

    if (func_ov102_0229d464(a, b) || func_ov102_0229d454(a, b)) {
        result = func_ov094_0229aaac(a + 0xcc, func_ov102_0229d400(a, b));
    } else {
        result = 0xfff1;
    }
    return result;
}
