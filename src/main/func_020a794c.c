/* func_020a794c @ 0x020a794c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a941c(void *);
extern int data_020e3e68;

void *func_020a794c(void *arg)
{
    *(int **) arg = &data_020e3e68;
    func_020a941c(arg);
    return arg;
}
