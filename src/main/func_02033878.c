/* func_02033878 @ 0x02033878, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

extern void *func_020339b8(void *);

void *func_02033878(void *p)
{
    __cxa_vec_cleanup((void *) (p), 0x18, 0x30, (((void (*)(void *)) func_020339b8)));
    return p;
}
