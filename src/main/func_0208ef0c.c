/* func_0208ef0c @ 0x0208ef0c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *) __attribute__((arm));
extern char data_020e236c;

void *func_0208ef0c(void *arg)
{
    *(void **) arg = (void *) &data_020e236c;
    func_0208a1f4((char *) arg + 0xc);
    func_0208af00(arg);
    func_020edb3c(arg);
    return arg;
}
