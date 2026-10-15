/* func_ov102_0229d8e0 @ 0x0229d8e0, 0x48 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f70(void *p);
extern void func_ov102_0229cc24(unsigned char *p, unsigned char b);
extern void func_ov102_0229c298(unsigned char *p, int n);
extern unsigned char *func_ov002_02208098(unsigned char *p, unsigned char value);
extern void func_ov102_0229cdf4(unsigned char *p);

void func_ov102_0229d8e0(unsigned char *param)
{
    if (func_ov002_02209f70(param + 0x2274) == 0) {
        func_ov102_0229cc24(param, param[0x25a6]);
        func_ov102_0229c298(param, 0x40);
        func_ov002_02208098(param, 0xc);
        func_ov102_0229cdf4(param);
    } else {
        func_ov002_02208098(param, 3);
    }
}
