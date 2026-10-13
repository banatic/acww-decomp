/* func_ov102_0229d0b0 @ 0x0229d0b0, 0x3a bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(void *, int);
extern int func_ov102_0229d454(void *, int);
extern int func_ov102_0229d400(void *, int);
extern int func_ov094_0229a8bc(void *, int);

int func_ov102_0229d0b0(char *arg0, int arg1)
{
    if (func_ov102_0229d464(arg0, arg1) != 0 || func_ov102_0229d454(arg0, arg1) != 0) {
        int c = func_ov102_0229d400(arg0, arg1);
        return func_ov094_0229a8bc(arg0 + 0xcc, c);
    } else {
        return 0;
    }
}
