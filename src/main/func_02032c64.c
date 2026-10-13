/* func_02032c64 @ 0x02032c64, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02032d38(void *);
extern void func_02032c7c(void *);

void *func_02032c64(void *arg)
{
    func_02032d38((char *) arg + 12);
    func_02032c7c(arg);
    return arg;
}
