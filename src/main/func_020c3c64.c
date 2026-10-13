/* func_020c3c64 @ 0x020c3c64, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201615c(void *);
extern char data_020e86ec;

void *func_020c3c64(void *arg)
{
    *(void **) arg = (void *) &data_020e86ec;
    func_0201615c(arg);
    return arg;
}
