/* func_ov102_0229cf90 @ 0x0229cf90, 0x4c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(unsigned char *p1, unsigned char *p2);
extern int func_ov102_0229d454(unsigned char *p1, unsigned char *p2);
extern int func_ov102_0229d400(unsigned char *p1, unsigned char *p2);
extern void func_ov102_0229cfdc(unsigned char *p);
extern void func_ov094_0229ab1c(unsigned char *p, int v);
extern void func_ov094_0229b98c(unsigned char *p);

void func_ov102_0229cf90(unsigned char *arg0, unsigned char *arg1)
{
    if (func_ov102_0229d464(arg0, arg1) || func_ov102_0229d454(arg0, arg1)) {
        int v = func_ov102_0229d400(arg0, arg1);
        func_ov094_0229ab1c(arg0 + 0xcc, v);
        func_ov094_0229b98c(arg0 + 0xb2c);
    } else {
        func_ov102_0229cfdc(arg0);
    }
}
