/* func_020ae3ec @ 0x020ae3ec, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ae720(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_020051b0(void);

void *func_020ae3ec(void *p)
{
    func_020ae720((char *) p + 8);
    __cxa_vec_cleanup(p, 3, 2, func_020051b0);
    return p;
}
