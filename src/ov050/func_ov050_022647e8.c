/* func_ov050_022647e8 @ 0x022647e8, 0x4c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_02260510(void *);
extern int func_ov050_022604bc(void *);
extern int func_ov050_022604e0(void *);
extern void func_ov050_02263640(void *, int);

int func_ov050_022647e8(void *arg)
{
    if (func_ov050_02260510(arg) != 0) {
        func_ov050_02263640((char *) arg + 0x658, 0);
    } else {
        if (func_ov050_022604bc(arg) != 0) {
            if (func_ov050_022604e0(arg) != 0) {
                ((char *) arg)[0x740] = 1;
            }
            func_ov050_02263640((char *) arg + 0x658, 0x11);
        }
    }
    return 1;
}
