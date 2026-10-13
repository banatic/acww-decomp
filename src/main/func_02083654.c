/* func_02083654 @ 0x02083654, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078ae4(void *);
extern void func_02083cb4(void *);

void *func_02083654(void *arg)
{
    func_02078ae4((char *) arg + 4);
    func_02083cb4(arg);
    return arg;
}
