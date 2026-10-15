/* func_02033c2c @ 0x02033c2c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_02033ca8(void *);

int func_02033c2c(int a)
{
    __cxa_vec_cleanup((void *) (a), 0x28, 0x40, (((void (*)(void *)) func_02033ca8)));
    return a;
}
