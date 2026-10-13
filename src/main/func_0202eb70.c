/* func_0202eb70 @ 0x0202eb70, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020161ac(void *arg);
extern int data_020d9ff8;

void *func_0202eb70(void *arg)
{
    func_020161ac(arg);
    *(void **) arg = &data_020d9ff8;
    return arg;
}
