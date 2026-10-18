/* func_0205347c @ 0x0205347c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *a, int b, int c, void (*dtor)(void *));
// 0x02053498: the elements' (empty) destructor
extern void func_02053498(void *);

void *func_0205347c(void *a)
{
    __cxa_vec_cleanup(a, 4, 20, func_02053498);
    return a;
}
