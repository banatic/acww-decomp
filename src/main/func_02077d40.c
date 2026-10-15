/* func_02077d40 @ 0x02077d40, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077c7c(void *);
extern void *func_02077c8c(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_02077d40(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 0x20, 0x24, (((void (*)(void *)) func_02077c8c)), (((void (*)(void *)) func_02077c7c)));
    return arg;
}
