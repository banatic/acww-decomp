/* func_ov128_0229be78 @ 0x0229be78, 0x30 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *p);
extern void func_ov128_0229bc30(void *p);
extern void func_ov002_02208098(void *p, unsigned char b);

void func_ov128_0229be78(unsigned char *param)
{
    if (func_0208e484(param + 0x110) != 0) {
        func_ov128_0229bc30(param);
        func_ov002_02208098(param, param[0x2d6a]);
    }
}
