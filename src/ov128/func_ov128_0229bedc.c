/* func_ov128_0229bedc @ 0x0229bedc, 0x30 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov128_0229c618(void *);
extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov128_0229bedc(void *param)
{
    if (func_ov002_02209f64((char *) param + 0x110) == 0) {
        func_ov002_02208098(param, *(unsigned char *) ((char *) param + 0x2d6a));
        func_ov128_0229c618(param);
    }
}
