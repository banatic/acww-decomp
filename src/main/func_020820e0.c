/* func_020820e0 @ 0x020820e0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *ptr);
extern char data_020e18d4;

void *func_020820e0(void *arg)
{
    *(void **) arg = &data_020e18d4;
    func_020a8c38(arg);
    return arg;
}
