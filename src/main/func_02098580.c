/* func_02098580 @ 0x02098580, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02099ad0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

int func_02098580(int arg)
{
    __cxa_vec_cleanup((void *) (arg), 3, 0x249C, (((void (*)(void *)) func_02099ad0)));
    return arg;
}
