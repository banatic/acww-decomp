/* func_0206da20 @ 0x0206da20, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *arg);
extern int data_020df228;

void *func_0206da20(void *arg)
{
    *((int *) arg) = (int) &data_020df228;
    func_020a8c38(arg);
    return arg;
}
