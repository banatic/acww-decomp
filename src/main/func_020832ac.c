/* func_020832ac @ 0x020832ac, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083cb8(void *);
extern void *func_0205efac(void *);

void *func_020832ac(void *arg)
{
    func_02083cb8(arg);
    func_0205efac((char *) arg + 4);
    return arg;
}
