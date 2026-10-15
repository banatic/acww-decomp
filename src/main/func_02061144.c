/* func_02061144 @ 0x02061144, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_02060a94(void *ptr);
extern void *func_02061444(void *);
extern void *func_02061470(void *);

void *func_02061144(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 5, 0x450, (((void (*)(void *)) func_02061470)), (((void (*)(void *)) func_02061444)));
    func_02060a94((void *) ((char *) arg + 0x1594));
    return arg;
}
