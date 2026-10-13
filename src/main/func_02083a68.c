/* func_02083a68 @ 0x02083a68, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083cb8(void *);
extern void func_02078a94(void *);
void *func_02083a68(void *arg)
{
    func_02083cb8(arg);
    func_02078a94((char *) arg + 4);
    return arg;
}
