/* func_ov003_02223b34 @ 0x02223b34, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *dest, int flag, int size, void (*func)(void));
extern void func_ov003_02223b18(void);

void *func_ov003_02223b34(void *p)
{
    __cxa_vec_cleanup((char *) p + 0x18a4, 4, 0x14c, func_ov003_02223b18);
    __cxa_vec_cleanup((char *) p + 0x14c0, 3, 0x14c, func_ov003_02223b18);
    __cxa_vec_cleanup((char *) p + 0x0f90, 4, 0x14c, func_ov003_02223b18);
    __cxa_vec_cleanup(p, 0xc, 0x14c, func_ov003_02223b18);
    return p;
}
