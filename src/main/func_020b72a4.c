/* func_020b72a4 @ 0x020b72a4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);
extern int data_020e5764;
extern int data_020e3c94;
extern int data_020da13c;

void *func_020b72a4(void *arg)
{
    *(volatile void **) arg = (void *) &data_020e5764;
    *(volatile void **) arg = (void *) &data_020e3c94;
    *(volatile void **) arg = (void *) &data_020da13c;
    func_020ee62c(arg);
    func_020edf54(arg);
    return arg;
}
