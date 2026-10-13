/* func_ov102_0229d074 @ 0x0229d074, 0x3a bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(void *a, int b);
extern int func_ov102_0229d454(void *a, int b);
extern int func_ov102_0229d400(void *a, int b);
extern int func_ov094_0229a69c(void *a, int b);

int func_ov102_0229d074(void *arg1, int arg2)
{
    if (func_ov102_0229d464(arg1, arg2) || func_ov102_0229d454(arg1, arg2)) {
        int temp = func_ov102_0229d400(arg1, arg2);
        arg1 = (char *) arg1 + 0xcc;
        return func_ov094_0229a69c(arg1, temp);
    }
    return 1;
}
