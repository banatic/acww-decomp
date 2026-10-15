/* func_02082528 @ 0x02082528, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_020795a8(void *);

void *func_02082528(void *arg)
{
    __cxa_vec_cleanup((void *) (arg), 8, 0x2c, (((void (*)(void *)) func_020795a8)));
    return arg;
}
