/* func_ov050_02264304 @ 0x02264304, 0x60 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern int func_020ada40(void);
extern int func_0208602c(void);
extern int func_02086108(int a, int b);
extern int func_020b5e10(void);
extern void func_020b6098(int a, int b);
extern void func_0203e020(void *ptr);
extern void func_ov050_02264834(void *ptr, int a);

int func_ov050_02264304(unsigned char *p)
{
    if (func_02014868(p + 0x618)) {
        return 1;
    }
    if (p[0x73c] != 0 && func_020ada40() == 0) {
        return 1;
    }
    if (func_02086108(func_0208602c(), 5) != 0) {
        func_020b6098(func_020b5e10(), 0);
    } else {
        func_0203e020(p);
    }
    func_ov050_02264834(p, 6);
    return 1;
}
