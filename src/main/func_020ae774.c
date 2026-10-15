/* func_020ae774 @ 0x020ae774, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *ptr);
extern void func_020a8c1c(void *ptr);
extern char data_020e4170;

void *func_020ae774(void *arg)
{
    func_020a8cac(arg);
    *(void **) arg = &data_020e4170;
    func_020a8c1c(arg);
    return arg;
}
