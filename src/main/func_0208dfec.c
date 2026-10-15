/* func_0208dfec @ 0x0208dfec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e21e4;
extern __thumb void *func_020a8c38(void *);
extern void func_020edb3c(void *);

void *func_0208dfec(void *arg)
{
    *(void **) arg = &data_020e21e4;
    func_020a8c38(arg);
    func_020edb3c(arg);
    return arg;
}
