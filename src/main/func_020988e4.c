/* func_020988e4 @ 0x020988e4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_02099ad0(void *);

int func_020988e4(int arg)
{
    __cxa_vec_cleanup((void *) (arg), 4, 0x249c, (((void (*)(void *)) func_02099ad0)));
    return arg;
}
