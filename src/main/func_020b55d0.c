/* func_020b55d0 @ 0x020b55d0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *arg);
extern void func_020a8c1c(void *arg);
extern char data_020e51d0[];

void *func_020b55d0(void *arg)
{
    func_020a8cac(arg);
    *(void **) arg = (void *) data_020e51d0;
    func_020a8c1c(arg);
    return arg;
}
