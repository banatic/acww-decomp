/* func_0206da38 @ 0x0206da38, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *p);
extern void func_020a8c1c(void *p);
extern int data_020df228;

void *func_0206da38(void *arg)
{
    func_020a8cac(arg);
    *(void **) arg = (void *) &data_020df228;
    func_020a8c1c(arg);
    return arg;
}
