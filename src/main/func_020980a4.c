/* func_020980a4 @ 0x020980a4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*handler)(void));

void *func_020980a4(void *p)
{
    __cxa_vec_cleanup(p, 10, 0x100, func_02066688);
    return p;
}
