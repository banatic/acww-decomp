/* func_020b4c5c @ 0x020b4c5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *);
extern void func_020edb3c(void *);
extern char data_020e5254;
extern char data_020e3e68;

void *func_020b4c5c(void *arg)
{
    *(void **) arg = &data_020e5254;
    *(void **) arg = &data_020e3e68;
    func_020a941c(arg);
    func_020edb3c(arg);
    return arg;
}
