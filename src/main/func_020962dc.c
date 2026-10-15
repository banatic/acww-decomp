/* func_020962dc @ 0x020962dc, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020012dc(void *);

void *func_020962dc(void *p)
{
    __cxa_vec_cleanup((void *) ((char *) p + 0x34), 4, 12, (void (*)(void *)) func_020012dc);
    return p;
}
