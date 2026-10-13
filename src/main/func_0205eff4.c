/* func_0205eff4 @ 0x0205eff4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd754;
extern void func_02056578(void *arg);

void *func_0205eff4(void *arg)
{
    *(void **) arg = &data_020dd754;
    func_02056578(arg);
    return arg;
}
