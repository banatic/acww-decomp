/* func_ov094_0229a2d0 @ 0x0229a2d0, 0x1c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *p, int a, int b, void (*cb)(void));
extern void func_02070be8(void);

void *func_ov094_0229a2d0(void *self)
{
    __cxa_vec_cleanup((char *) self + 0xe0, 2, 0x6c, func_02070be8);
    return self;
}
