/* func_0206921c @ 0x0206921c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020defc0, data_020e3e68;
extern void func_020a941c(volatile int *p, int x);

volatile int *func_0206921c(volatile int *p)
{
    *p = (int) &data_020defc0;
    *p = (int) &data_020e3e68;
    func_020a941c(p, (int) &data_020e3e68);
    return p;
}
