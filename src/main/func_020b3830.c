/* func_020b3830 @ 0x020b3830, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b39b8(void *);
extern void func_020b38b0(void *);

void *func_020b3830(void *arg)
{
    func_020b39b8(arg);
    func_020b38b0((char *) arg + 4);
    return arg;
}
