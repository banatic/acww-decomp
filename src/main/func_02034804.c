/* func_02034804 @ 0x02034804, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02034820(void *);

void *func_02034804(void *ptr)
{
    __cxa_vec_cleanup((void *) (ptr), 0x24, 8, (void (*)(void *)) func_02034820);
    return ptr;
}
