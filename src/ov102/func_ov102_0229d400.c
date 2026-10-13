/* func_ov102_0229d400 @ 0x0229d400, 0x36 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(int a, int b);
extern int func_ov102_0229d454(int a, int b);
extern int func_ov102_0229d288(int a, int b);

int func_ov102_0229d400(int a, int b)
{
    if (func_ov102_0229d464(a, b) != 0) {
        return (unsigned char) b;
    }
    if (func_ov102_0229d454(a, b) != 0) {
        return func_ov102_0229d288(a, b);
    }
    return 0;
}
