/* func_02072b18 @ 0x02072b18, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_02072da4(void *);

void *func_02072b18(void *ptr)
{
    __cxa_vec_cleanup((void *) (ptr), 8, 0x234, (((void (*)(void *)) func_02072da4)));
    return ptr;
}
