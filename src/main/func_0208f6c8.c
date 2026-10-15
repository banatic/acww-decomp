/* func_0208f6c8 @ 0x0208f6c8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *a);

extern unsigned char data_020da13c[];
extern unsigned char data_020e241c[];

void *func_0208f6c8(void *arg)
{
    *(void **) arg = (void *) data_020e241c;
    *(void **) arg = (void *) data_020da13c;
    func_020ee62c(arg);
    return arg;
}
