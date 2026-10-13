/* func_02062fbc @ 0x02062fbc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_020de62c;

void *func_02062fbc(void *arg)
{
    func_020a8cac(arg);
    *(void **) arg = &data_020de62c;
    func_020a8c1c(arg);
    return arg;
}
