/* func_0208afb4 @ 0x0208afb4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c();
extern void func_020edf54();

extern unsigned char data_020da13c[];
extern unsigned char data_020e2288[];

void *func_0208afb4(void *arg)
{
    *(int *) arg = (unsigned int) data_020e2288;
    *(int *) arg = (unsigned int) data_020da13c;
    func_020ee62c(arg);
    func_020edf54(arg);
    return arg;
}
