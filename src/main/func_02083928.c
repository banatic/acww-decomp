/* func_02083928 @ 0x02083928, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083cb8(void *);
extern void func_02078a54(void *);

void *func_02083928(void *arg)
{
    func_02083cb8(arg);
    func_02078a54((char *) arg + 4);
    return arg;
}
