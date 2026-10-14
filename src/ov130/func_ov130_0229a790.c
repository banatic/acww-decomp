/* func_ov130_0229a790 @ 0x0229a790, 0x1c bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_02070be8(void);

void *func_ov130_0229a790(void *arg)
{
    __cxa_vec_cleanup((char *) arg + 0x2c, 5, 0x6c, func_02070be8);
    return arg;
}
